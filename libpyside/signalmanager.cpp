/*
* This file is part of the Shiboken Python Bindings Generator project.
*
* Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
*
* Contact: PySide team <contact@pyside.org>
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public License
* version 2.1 as published by the Free Software Foundation. Please
* review the following information to ensure the GNU Lesser General
* Public License version 2.1 requirements will be met:
* http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
*
* As a special exception to the GNU Lesser General Public License
* version 2.1, the object code form of a "work that uses the Library"
* may incorporate material from a header file that is part of the
* Library.  You may distribute such object code under terms of your
* choice, provided that the incorporated material (i) does not exceed
* more than 5% of the total size of the Library; and (ii) is limited to
* numerical parameters, data structure layouts, accessors, macros,
* inline functions and templates.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
* 02110-1301 USA
*/

#include "signalmanager.h"
#include "proxyslot.h"
#include <QHash>
#include <QStringList>
#include <QDebug>

#if QSLOT_CODE != 1 || QSIGNAL_CODE != 2
#error QSLOT_CODE and/or QSIGNAL_CODE changed! change the hardcoded stuff to the correct value!
#endif
#define PYSIDE_SLOT '1'
#define PYSIDE_SIGNAL '2'
#include "typeresolver.h"
#include "signalslotconnection.h"

using namespace PySide;

static bool checkSignal(const char* signal)
{
    if (signal[0] != PYSIDE_SIGNAL) {
        PyErr_SetString(PyExc_TypeError, "Use the function PySide.QtCore.SIGNAL on signals");
        return false;
    }
    return true;
}

QStringList PySide::getArgsFromSignature(const char* signature)
{
    QString qsignature(signature);
    QStringList result;
    QRegExp splitRegex("\\s*,\\s*");

    if (qsignature.contains("()") || qsignature.contains("(void)")) {
        return result;
    } else if (qsignature.contains('(')) {
        //get args types
        QString types = qsignature.replace(QRegExp(".+\\((.*)\\)"), "\\1");
        result = types.split(splitRegex);
    }
    return result;
}

struct SignalManager::SignalManagerPrivate
{
    QHash<const QObject*, ProxySlot*> m_proxies;

    ProxySlot* findProxy(const QObject* signalSource) const
    {
        return m_proxies.value(signalSource);
    }

    ProxySlot* getProxy(const QObject* signalSource)
    {
        ProxySlot* proxy = findProxy(signalSource);
        if (!proxy) {
            proxy = new ProxySlot(signalSource);
            m_proxies[signalSource] = proxy;
            QObject::connect(signalSource, SIGNAL(destroyed()), proxy, SLOT(deleteLater()));
        }
        return proxy;
    }
};

SignalManager::SignalManager() : m_d(new SignalManagerPrivate)
{
}

SignalManager::~SignalManager()
{
    delete m_d;
}

SignalManager& SignalManager::instance()
{
    static SignalManager me;
    return me;
}

bool SignalManager::connect(QObject* source, const char* signal, PyObject* callback, Qt::ConnectionType type)
{
    if (!checkSignal(signal))
        return false;
    signal++;

    ProxySlot* proxy = m_d->getProxy(source);
    if (source->metaObject()->indexOfSignal(signal) == -1)
        proxy->dynamicQMetaObject()->addSignal(signal);
    AbstractQObjectConnection* connection = new SignalSlotConnection(source, signal, callback, type);
    return proxy->connect(connection);
}

bool SignalManager::connect(QObject* source, const char* signal, QObject* receiver, const char* slot, Qt::ConnectionType type)
{
    if (!checkSignal(signal))
        return false;

    if (!QMetaObject::checkConnectArgs(signal, slot))
        return false;
    int signal_index = source->metaObject()->indexOfSignal(signal);
    int slot_index = receiver->metaObject()->indexOfSlot(slot);

    bool retval;
    if (signal_index != -1 && slot_index != -1) {
        // C++ -> C++ connection
        retval = QMetaObject::connect(source, signal_index,
                                      receiver, slot_index, type);
    } else {
        // We have a python slot or signal
        ProxySlot* proxy = m_d->getProxy(source);
        AbstractQObjectConnection* connection = 0;
        retval = proxy->connect(connection);
    }
    return retval;

}

bool SignalManager::emitSignal(QObject* source, const char* signal, PyObject* args)
{
    if (!checkSignal(signal))
        return false;
    signal++;

    int argsGiven = PySequence_Size(args);

    int signalIndex = source->metaObject()->indexOfSignal(signal);
    if (signalIndex != -1) {
        QStringList argTypes = getArgsFromSignature(signal);
        void* signalArgs[argsGiven+1];

        for (int i = 0; i < argsGiven; i++)
            signalArgs[i] = TypeResolver::get(argTypes[i])->toCpp(PySequence_GetItem(args, i));

        QMetaObject::activate(source, signalIndex, signalArgs);
        return true;
    }
    return false;
}

void PySide::SignalManager::removeProxySlot(const QObject* signalSource)
{
    m_d->m_proxies.remove(signalSource);
}

const QMetaObject* PySide::SignalManager::getMetaObject(const QObject* object) const
{
    ProxySlot* proxy = m_d->findProxy(object);
    if (proxy)
        return proxy->dynamicQMetaObject()->metaObject();
    return 0;
}

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

#include <QHash>
#include <QStringList>
#include <QMetaMethod>
#include <autodecref.h>
#include <QDebug>
#include <limits>

#if QSLOT_CODE != 1 || QSIGNAL_CODE != 2
#error QSLOT_CODE and/or QSIGNAL_CODE changed! change the hardcoded stuff to the correct value!
#endif
#define PYSIDE_SLOT '1'
#define PYSIDE_SIGNAL '2'
#include "typeresolver.h"
#include "globalreceiver.h"

using namespace PySide;

bool PySide::isSignal(const char* signal)
{
    return signal[0] == PYSIDE_SIGNAL;
}

bool PySide::checkSignal(const char* signal)
{
    if (signal[0] != PYSIDE_SIGNAL) {
        PyErr_SetString(PyExc_TypeError, "Use the function PySide.QtCore.SIGNAL on signals");
        return false;
    }
    return true;
}

QString PySide::getCallbackSignature(const char* signal, PyObject* callback)
{
    PyObject* function;
    int useSelf = PyMethod_Check(callback);
    if (useSelf) {
        function = PyMethod_GET_FUNCTION(callback);
    } else {
        function = callback;
    }

    PyCodeObject* objCode = reinterpret_cast<PyCodeObject*>(PyFunction_GET_CODE(function));
    QString signature(PyString_AS_STRING(objCode->co_name));
    signature.append(QString::number(quint64(callback), 16));
    signature.append('(');
    int numArgs = objCode->co_flags & CO_VARARGS ? -1 : objCode->co_argcount;

    QStringList args = getArgsFromSignature(signal);
    if (numArgs == -1)
        numArgs = std::numeric_limits<int>::max();
    while (args.count() > numArgs - useSelf) {
        args.removeLast();
    }
    signature.append(args.join(","));
    signature.append(')');
    return signature;
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
    GlobalReceiver m_globalReceiver;
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

QObject* SignalManager::globalReceiver()
{
    return &m_d->m_globalReceiver;
}

void SignalManager::addGlobalSlot(const char* slot, PyObject* callback)
{
    m_d->m_globalReceiver.addSlot(slot, callback);
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
        if (argsGiven > argTypes.count()) {
            PyErr_SetString(PyExc_TypeError, "Too many arguments for this signal.");
            return false;
        }
        void* signalArgs[argsGiven+1];
        signalArgs[0] = 0;
        for (int i = 0; i < argsGiven; ++i)
            signalArgs[i+1] = TypeResolver::get(argTypes[i])->toCpp(PySequence_GetItem(args, i));
        QMetaObject::activate(source, signalIndex, signalArgs);
        // FIXME: This will cause troubles with non-direct connections.
        for (int i = 0; i < argsGiven; ++i)
            TypeResolver::get(argTypes[i])->deleteObject(signalArgs[i+1]);
        return true;
    }
    return false;
}

int PySide::SignalManager::qt_metacall(QObject* object, QMetaObject::Call call, int id, void** args)
{
    const QMetaObject* metaObject = object->metaObject();
    // only meta method invocation is supported right now.
    if (call != QMetaObject::InvokeMetaMethod) {
        qWarning("Only meta method invocation is supported right now by PySide.");
        return id - metaObject->methodCount();
    }
    QMetaMethod method = metaObject->method(id);

    if (method.methodType() == QMetaMethod::Signal) {
        // emit python signal
        QMetaObject::activate(object, id, args);
    } else {
        // call python slot
        QList<QByteArray> paramTypes = method.parameterTypes();
        PyObject* self = Shiboken::BindingManager::instance().retrieveWrapper(object);
        Shiboken::AutoDecRef preparedArgs(PyTuple_New(paramTypes.count()+1));

        PyTuple_SET_ITEM(preparedArgs.object(), 0, self);
        for (int i = 0, max = paramTypes.count(); i < max; ++i) {
            PyObject* arg = TypeResolver::get(paramTypes[i].constData())->toPython(args[i+1]);
            PyTuple_SET_ITEM(preparedArgs.object(), i + 1, arg);
        }

        QString methodName = method.signature();
        methodName = methodName.left(methodName.indexOf('('));

        Shiboken::AutoDecRef pyMethodName(PyString_FromString(qPrintable(methodName)));
        Shiboken::AutoDecRef pyMethod(PyObject_GetAttr(self, pyMethodName));
        Shiboken::AutoDecRef retval(PyObject_CallObject(pyMethod, preparedArgs));
        if (!retval)
            qWarning("Error calling slot");
    }
    return -1;
}

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
#include <typeresolver.h>

#if QSLOT_CODE != 1 || QSIGNAL_CODE != 2
#error QSLOT_CODE and/or QSIGNAL_CODE changed! change the hardcoded stuff to the correct value!
#endif
#define PYSIDE_SLOT '1'
#define PYSIDE_SIGNAL '2'
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

static QString codeCallbackName(PyObject* callback, const QString& funcName)
{
    return funcName+QString::number(quint64(callback), 16);
}

QString PySide::getCallbackSignature(const char* signal, PyObject* callback, bool encodeName)
{
    QString functionName;
    int numArgs = -1;
    bool useSelf = false;

    bool isMethod = PyMethod_Check(callback);
    bool isFunction = PyFunction_Check(callback);

    if (isMethod || isFunction) {
        PyObject* function = isMethod ? PyMethod_GET_FUNCTION(callback) : callback;
        PyCodeObject* objCode = reinterpret_cast<PyCodeObject*>(PyFunction_GET_CODE(function));
        functionName = PyString_AS_STRING(objCode->co_name);
        useSelf = isMethod;
        numArgs = objCode->co_flags & CO_VARARGS ? -1 : objCode->co_argcount;
    } else if (PyCFunction_Check(callback)) {
        functionName = ((PyCFunctionObject*)callback)->m_ml->ml_name;
        useSelf = ((PyCFunctionObject*)callback)->m_self;
        int flags = ((PyCFunctionObject*)callback)->m_ml->ml_flags;
        if (flags & METH_O)
            numArgs = 1;
        else if (flags & METH_VARARGS)
            numArgs = -1;
        else if (flags & METH_NOARGS)
            numArgs = 0;
    }
    Q_ASSERT(!functionName.isEmpty());

    QString signature;
    if (encodeName)
        signature = codeCallbackName(callback, functionName);
    else
        signature = functionName;

    bool isShortCircuit;
    QStringList args = getArgsFromSignature(signal, &isShortCircuit);

    if (!isShortCircuit) {
        signature.append('(');
        if (numArgs == -1)
            numArgs = std::numeric_limits<int>::max();
        while (args.count() && args.count() > numArgs - useSelf) {
            args.removeLast();
        }
        signature.append(args.join(","));
        signature.append(')');
    }
    return signature;
}

QStringList PySide::getArgsFromSignature(const char* signature, bool* isShortCircuit)
{
    QString qsignature(signature);
    QStringList result;
    QRegExp splitRegex("\\s*,\\s*");

    if (isShortCircuit)
        *isShortCircuit = !qsignature.contains('(');
    if (qsignature.contains("()") || qsignature.contains("(void)")) {
        return result;
    } else if (qsignature.contains('(')) {
        static QRegExp regex(".+\\((.*)\\)");
        //get args types
        QString types = qsignature.replace(regex, "\\1");
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
    // Register Qt primitive typedefs used on signals.
    using namespace Shiboken;
    TypeResolver::createValueTypeResolver<qint8>("qint8");
    TypeResolver::createValueTypeResolver<qint16>("qint16");
    TypeResolver::createValueTypeResolver<qint32>("qint32");
    TypeResolver::createValueTypeResolver<qint64>("qint64");
    TypeResolver::createValueTypeResolver<qlonglong>("qlonglong");
    TypeResolver::createValueTypeResolver<qptrdiff>("qptrdiff");
    TypeResolver::createValueTypeResolver<qreal>("qreal");
    TypeResolver::createValueTypeResolver<quint8>("quint8");
    TypeResolver::createValueTypeResolver<quint16>("quint16");
    TypeResolver::createValueTypeResolver<quint32>("quint32");
    TypeResolver::createValueTypeResolver<quint64>("quint64");
    TypeResolver::createValueTypeResolver<quintptr>("quintptr");
    TypeResolver::createValueTypeResolver<qulonglong>("qulonglong");
    TypeResolver::createValueTypeResolver<uchar>("uchar");
    TypeResolver::createValueTypeResolver<uint>("uint");
    TypeResolver::createValueTypeResolver<ulong>("ulong");
    TypeResolver::createValueTypeResolver<ushort>("ushort");
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

void SignalManager::globalReceiverConnectNotify(int slotIndex)
{
    m_d->m_globalReceiver.connectNotify(slotIndex);
}

void SignalManager::globalReceiverDisconnectNotify(int slotIndex)
{
    m_d->m_globalReceiver.disconnectNotify(slotIndex);
}

void SignalManager::addGlobalSlot(const char* slot, PyObject* callback)
{
    m_d->m_globalReceiver.addSlot(slot, callback);
}

static bool emitShortCircuitSignal(QObject* source, int signalIndex, PyObject* args)
{
    void* signalArgs[2] = {0, args};
    QMetaObject::activate(source, signalIndex, signalArgs);
    return true;
}

static bool emitNormalSignal(QObject* source, int signalIndex, const char* signal, PyObject* args, const QStringList& argTypes)
{
    int argsGiven = PySequence_Size(args);
    if (argsGiven > argTypes.count()) {
        QString msg = QString("%1 only accepts %2 arguments, %3 given!").arg(signal).arg(argTypes.count()).arg(argsGiven);
        PyErr_SetString(PyExc_TypeError, msg.toLocal8Bit().constData());
        return false;
    }

    void* signalArgs[argsGiven+1];
    signalArgs[0] = 0;

    for (int i = 0; i < argsGiven; ++i)
        signalArgs[i+1] = Shiboken::TypeResolver::get(qPrintable(argTypes[i]))->toCpp(PySequence_GetItem(args, i));
    QMetaObject::activate(source, signalIndex, signalArgs);
    // FIXME: This will cause troubles with non-direct connections.
    for (int i = 0; i < argsGiven; ++i)
        Shiboken::TypeResolver::get(qPrintable(argTypes[i]))->deleteObject(signalArgs[i+1]);
    return true;
}

bool SignalManager::emitSignal(QObject* source, const char* signal, PyObject* args)
{
    if (!checkSignal(signal))
        return false;
    signal++;


    int signalIndex = source->metaObject()->indexOfSignal(signal);
    if (signalIndex != -1) {
        bool isShortCircuit;
        QStringList argTypes = getArgsFromSignature(signal, &isShortCircuit);

        if (isShortCircuit)
            return emitShortCircuitSignal(source, signalIndex, args);
        else
            return emitNormalSignal(source, signalIndex, signal, args, argTypes);
    }
    qWarning() << "Error emitting signal: " << signal;
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
        Shiboken::AutoDecRef preparedArgs(PyTuple_New(paramTypes.count()));

        for (int i = 0, max = paramTypes.count(); i < max; ++i) {
            PyObject* arg = Shiboken::TypeResolver::get(paramTypes[i].constData())->toPython(args[i+1]);
            PyTuple_SET_ITEM(preparedArgs.object(), i, arg);
        }

        QString methodName = method.signature();
        methodName = methodName.left(methodName.indexOf('('));

        Shiboken::AutoDecRef pyMethod(PyObject_GetAttrString(self, qPrintable(methodName)));
        if (pyMethod) {
            Shiboken::AutoDecRef retval(PyObject_CallObject(pyMethod, preparedArgs));
            if (!retval)
                qWarning() << "Error calling slot" << methodName;
        } else {
            qWarning() << "Dynamic slot" << methodName << "not found!";
        }
    }
    return -1;
}

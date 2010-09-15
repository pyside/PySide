/*
* This file is part of the PySide project.
*
* Copyright (C) 2009-2010 Nokia Corporation and/or its subsidiary(-ies).
*
* Contact: PySide team <contact@pyside.org>
*
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "signalmanager.h"
#include "qproperty.h"

#include <QHash>
#include <QStringList>
#include <QMetaMethod>
#include <autodecref.h>
#include <gilstate.h>
#include <QDebug>
#include <limits>
#include <typeresolver.h>
#include <basewrapper.h>
#include <conversions.h>

#if QSLOT_CODE != 1 || QSIGNAL_CODE != 2
#error QSLOT_CODE and/or QSIGNAL_CODE changed! change the hardcoded stuff to the correct value!
#endif
#define PYSIDE_SLOT '1'
#define PYSIDE_SIGNAL '2'
#include "globalreceiver.h"

#define PYTHON_TYPE "PyObject"

namespace PySide {

PyObjectWrapper::PyObjectWrapper()
    :m_me(Py_None)
{
    Py_INCREF(m_me);
}

PyObjectWrapper::PyObjectWrapper(PyObject* me)
    : m_me(me)
{
    Py_INCREF(m_me);
}

PyObjectWrapper::PyObjectWrapper(const PyObjectWrapper &other)
    : m_me(other.m_me)
{
    Py_INCREF(m_me);
}

PyObjectWrapper::~PyObjectWrapper()
{
    Py_DECREF(m_me);
}


PyObjectWrapper::operator PyObject*() const
{
    return m_me;
}

};

namespace Shiboken {

template<>
struct Converter<PySide::PyObjectWrapper>
{
    static PySide::PyObjectWrapper toCpp(PyObject* obj)
    {
        return PySide::PyObjectWrapper(obj);
    }

    static PyObject* toPython(void* obj)
    {
        return toPython(*reinterpret_cast<PySide::PyObjectWrapper*>(obj));
    }

    static PyObject* toPython(const PySide::PyObjectWrapper& obj)
    {
        Py_INCREF((PyObject*)obj);
        return obj;
    }
};

};


using namespace PySide;

bool PySide::isSignal(const char* signal)
{
    return (signal && signal[0] == PYSIDE_SIGNAL);
}

bool PySide::checkSignal(const char* signal)
{
    if (!signal)
        return false;

    if (signal[0] != PYSIDE_SIGNAL) {
        PyErr_SetString(PyExc_TypeError, "Use the function PySide.QtCore.SIGNAL on signals");
        return false;
    }
    return true;
}

static QString codeCallbackName(PyObject* callback, const QString& funcName)
{
    if (PyMethod_Check(callback)) {
        PyObject *self = PyMethod_GET_SELF(callback);
        PyObject *func = PyMethod_GET_FUNCTION(callback);
        return funcName + QString::number(quint64(self), 16) + QString::number(quint64(func), 16);
    } else
        return funcName+QString::number(quint64(callback), 16);
}

QString PySide::getCallbackSignature(const char* signal, QObject* receiver, PyObject* callback, bool encodeName)
{
    QString functionName;
    QString signature;
    QStringList args;
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

        if (receiver) {
            //Search for signature on metaobject
            const QMetaObject *mo = receiver->metaObject();
            for(int i=0; i < mo->methodCount(); i++) {
            QMetaMethod me = mo->method(i);
                if (QString(me.signature()).startsWith(functionName)) {
                    numArgs = me.parameterTypes().size()+1;
                    break;
                }
           }
        }

        if (numArgs == -1) {
            if (flags & METH_O)
                numArgs = 1;
            else if (flags & METH_VARARGS)
                numArgs = -1;
            else if (flags & METH_NOARGS)
                numArgs = 0;
        }
    } else if (PyCallable_Check(callback)) {
        functionName = "__callback"+QString::number((size_t)callback);
    }

    Q_ASSERT(!functionName.isEmpty());

    bool isShortCircuit = false;

    if (encodeName)
        signature = codeCallbackName(callback, functionName);
    else
        signature = functionName;

    args = getArgsFromSignature(signal, &isShortCircuit);

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

    // Register PyObject type to use in queued signal and slot connections
    qRegisterMetaType<PyObjectWrapper>(PYTHON_TYPE);

    TypeResolver::createValueTypeResolver<PyObjectWrapper>(PYTHON_TYPE);
    TypeResolver::createValueTypeResolver<PyObjectWrapper>("object");
    TypeResolver::createValueTypeResolver<PyObjectWrapper>("PySide::PyObjectWrapper");
}

void SignalManager::clear()
{
    delete m_d;
    m_d = new SignalManagerPrivate();
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

void SignalManager::globalReceiverConnectNotify(QObject* source, int slotIndex)
{
    m_d->m_globalReceiver.connectNotify(source, slotIndex);
}

void SignalManager::globalReceiverDisconnectNotify(QObject* source, int slotIndex)
{
    m_d->m_globalReceiver.disconnectNotify(source, slotIndex);
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
    Shiboken::AutoDecRef sequence(PySequence_Fast(args, 0));
    int argsGiven = PySequence_Fast_GET_SIZE(sequence.object());
    if (argsGiven > argTypes.count()) {
        PyErr_Format(PyExc_TypeError, "%s only accepts %d arguments, %d given!", signal, argTypes.count(), argsGiven);
        return false;
    }

    void** signalArgs = new void*[argsGiven+1];
    signalArgs[0] = 0;

    int i;
    for (i = 0; i < argsGiven; ++i) {
        Shiboken::TypeResolver* typeResolver = Shiboken::TypeResolver::get(qPrintable(argTypes[i]));
        if (typeResolver) {
            void *data = typeResolver->toCpp(PySequence_Fast_GET_ITEM(sequence.object(), i));
            if (Shiboken::TypeResolver::getType(qPrintable(argTypes[i])) == Shiboken::TypeResolver::ObjectType) {
                signalArgs[i+1] = &data;
            } else {
                signalArgs[i+1] = data;
            }
        } else {
            PyErr_Format(PyExc_TypeError, "Unknown type used to emit a signal: %s", qPrintable(argTypes[i]));
            break;
        }
    }

    bool ok = i == argsGiven;
    if (ok)
        QMetaObject::activate(source, signalIndex, signalArgs);

    // FIXME: This will cause troubles with non-direct connections.
    for (int j = 0; j < i; ++j)
        Shiboken::TypeResolver::get(qPrintable(argTypes[j]))->deleteObject(signalArgs[j+1]);

    delete[] signalArgs;

    return ok;
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
    return false;
}

int SignalManager::qt_metacall(QObject* object, QMetaObject::Call call, int id, void** args)
{
    const QMetaObject* metaObject = object->metaObject();
    PyObject* pp = 0;
    PyObject* pp_name = 0;
    QMetaProperty mp;
    Shiboken::TypeResolver* typeResolver = 0;
    PyObject* pySelf = Shiboken::BindingManager::instance().retrieveWrapper(object);

    if (call != QMetaObject::InvokeMetaMethod) {
        mp = metaObject->property(id);
        if (!mp.isValid())
            return id - metaObject->methodCount();

        pp_name = PyString_FromString(mp.name());
        pp = qproperty_get_object(pySelf, pp_name);
        if (!pp) {
            qWarning("Invalid property.");
            Py_XDECREF(pp_name);
            return id - metaObject->methodCount();
        }
        typeResolver = Shiboken::TypeResolver::get(mp.typeName());
    }

    switch(call) {
#ifndef QT_NO_PROPERTIES
        case QMetaObject::ReadProperty:
        {
            PyObject* value = qproperty_get(pp, pySelf);
            if (value) {
                void *data = typeResolver->toCpp(value);
                if (Shiboken::TypeResolver::getType(mp.typeName()) == Shiboken::TypeResolver::ObjectType)
                    args[0] = &data;
                else
                    args[0] = data;

                Py_DECREF(value);
            } else if (PyErr_Occurred()) {
                PyErr_Print(); // Clear any errors but print them to stderr
            }
            break;
        }

        case QMetaObject::WriteProperty:
        {
            Shiboken::AutoDecRef value(typeResolver->toPython(args[0]));
            qproperty_set(pp, pySelf, value);
            break;
        }

        case QMetaObject::ResetProperty:
            qproperty_reset(pp, pp_name);
            break;

        case QMetaObject::QueryPropertyDesignable:
        case QMetaObject::QueryPropertyScriptable:
        case QMetaObject::QueryPropertyStored:
        case QMetaObject::QueryPropertyEditable:
        case QMetaObject::QueryPropertyUser:
            break;
#endif
        case QMetaObject::InvokeMetaMethod:
            id = call_method(object, id, args);
            break;

        default:
            qWarning("Unsupported meta invocation type.");
    }

    if (call == QMetaObject::InvokeMetaMethod)
        id = id - metaObject->methodCount();
    else
        id = id - metaObject->propertyCount();

    Py_XDECREF(pp);
    Py_XDECREF(pp_name);
    return id;
}

int SignalManager::call_method(QObject* object, int id, void** args)
{
    const QMetaObject* metaObject = object->metaObject();
    QMetaMethod method = metaObject->method(id);

    if (method.methodType() == QMetaMethod::Signal) {
        // emit python signal
        QMetaObject::activate(object, id, args);
    } else {
        // call python slot
        Shiboken::GilState gil;
        QList<QByteArray> paramTypes = method.parameterTypes();
        PyObject* self = Shiboken::BindingManager::instance().retrieveWrapper(object);
        PyObject* preparedArgs = NULL;
        Py_ssize_t args_size = paramTypes.count();

        if (args_size)
            preparedArgs = PyTuple_New(args_size);

        for (int i = 0, max = paramTypes.count(); i < max; ++i) {
            void* data = args[i+1];
            const char* dataType = paramTypes[i].constData();

            PyObject* arg = Shiboken::TypeResolver::get(dataType)->toPython(data);
            PyTuple_SET_ITEM(preparedArgs, i, arg);
        }

        QString methodName = method.signature();
        methodName = methodName.left(methodName.indexOf('('));

        Shiboken::AutoDecRef pyMethod(PyObject_GetAttrString(self, qPrintable(methodName)));
        if (!pyMethod.isNull()) {
            Shiboken::AutoDecRef retval(PyObject_CallObject(pyMethod, preparedArgs));
            if (retval.isNull()) {
                qWarning() << "Error calling slot" << methodName;
                PyErr_Print();
            }
        } else {
            qWarning() << "Dynamic slot" << methodName << "not found!";
        }
        Py_XDECREF(preparedArgs);
    }
    return -1;
}

bool SignalManager::registerMetaMethod(QObject* source, const char* signature, QMetaMethod::MethodType type)
{
    Q_ASSERT(source);
    const QMetaObject* metaObject = source->metaObject();
    int methodIndex = metaObject->indexOfMethod(signature);
    // Create the dynamic signal is needed
    if (methodIndex == -1) {
        Shiboken::SbkBaseWrapper* self = (Shiboken::SbkBaseWrapper*) Shiboken::BindingManager::instance().retrieveWrapper(source);
        if (!self->containsCppWrapper) {
            qWarning() << "You can't add dynamic signals or slots on an object originated from C++.";
            return false;
        } else {
            PySide::DynamicQMetaObject* dynMetaObj = reinterpret_cast<PySide::DynamicQMetaObject*>(const_cast<QMetaObject*>(metaObject));
            if (type == QMetaMethod::Signal)
                dynMetaObj->addSignal(signature);
            else
                dynMetaObj->addSlot(signature);
        }
    }
    return true;
}

bool SignalManager::hasConnectionWith(const QObject *object)
{
    return m_d->m_globalReceiver.hasConnectionWith(object);
}

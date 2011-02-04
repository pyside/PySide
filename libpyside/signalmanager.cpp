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
#include "pysidesignal.h"
#include "pysideproperty.h"
#include "pysideproperty_p.h"
#include "pyside.h"

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

static int callMethod(QObject* object, int id, void** args);

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
    Shiboken::GilState gil;
    Py_DECREF(m_me);
}

PyObjectWrapper& PyObjectWrapper::operator=(const PySide::PyObjectWrapper& other)
{
    Py_INCREF(other.m_me);
    Py_DECREF(m_me);
    m_me = other.m_me;
    return *this;
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

struct SignalManager::SignalManagerPrivate
{
    GlobalReceiver m_globalReceiver;
};

static void clearSignalManager()
{
    PySide::SignalManager::instance().clear();
}

SignalManager::SignalManager() : m_d(new SignalManagerPrivate)
{
    // Register Qt primitive typedefs used on signals.
    using namespace Shiboken;

    // Register PyObject type to use in queued signal and slot connections
    qRegisterMetaType<PyObjectWrapper>(PYTHON_TYPE);

    TypeResolver::createValueTypeResolver<PyObjectWrapper>(PYTHON_TYPE);
    TypeResolver::createValueTypeResolver<PyObjectWrapper>("object");
    TypeResolver::createValueTypeResolver<PyObjectWrapper>("PySide::PyObjectWrapper");
    PySide::registerCleanupFunction(clearSignalManager);
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
    source->qt_metacall(QMetaObject::InvokeMetaMethod, signalIndex, signalArgs);
    return true;
}

static bool emitNormalSignal(QObject* source, int signalIndex, const char* signal, PyObject* args, const QStringList& argTypes)
{
    Shiboken::AutoDecRef sequence(PySequence_Fast(args, 0));
    int argsGiven = PySequence_Fast_GET_SIZE(sequence.object());

    if (argsGiven != argTypes.count()) {
        PyErr_Format(PyExc_TypeError, "%s only accepts %d arguments, %d given!", signal, argTypes.count(), argsGiven);
        return false;
    }

    QVariant* signalValues = new QVariant[argsGiven];
    void** signalArgs = new void*[argsGiven + 1];
    signalArgs[0] = 0;

    int i;
    for (i = 0; i < argsGiven; ++i) {
        QByteArray typeName = argTypes[i].toAscii();
        Shiboken::TypeResolver* typeResolver = Shiboken::TypeResolver::get(typeName);
        if (typeResolver) {
            if (Shiboken::TypeResolver::getType(typeName) == Shiboken::TypeResolver::ValueType) {
                int typeId = QMetaType::type(typeName);
                if (!typeId) {
                    PyErr_Format(PyExc_TypeError, "Value type used on signal needs to be registered on meta type: %s", typeName.data());
                    break;
                }
                signalValues[i] = QVariant(typeId, (void*) 0);
            }
            signalArgs[i+1] = signalValues[i].data();
            typeResolver->toCpp(PySequence_Fast_GET_ITEM(sequence.object(), i), &signalArgs[i+1]);
        } else {
            PyErr_Format(PyExc_TypeError, "Unknown type used to emit a signal: %s", qPrintable(argTypes[i]));
            break;
        }
    }

    bool ok = i == argsGiven;
    if (ok)
        source->qt_metacall(QMetaObject::InvokeMetaMethod, signalIndex, signalArgs);

    delete[] signalArgs;
    delete[] signalValues;

    return ok;
}

bool SignalManager::emitSignal(QObject* source, const char* signal, PyObject* args)
{
    if (!Signal::checkQtSignal(signal))
        return false;
    signal++;

    int signalIndex = source->metaObject()->indexOfSignal(signal);
    if (signalIndex != -1) {
        bool isShortCircuit;
        QStringList argTypes = Signal::getArgsFromSignature(signal, &isShortCircuit);

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
    PySideProperty* pp = 0;
    PyObject* pp_name = 0;
    QMetaProperty mp;
    PyObject* pySelf = 0;

    if (call != QMetaObject::InvokeMetaMethod) {
        mp = metaObject->property(id);
        if (!mp.isValid())
            return id - metaObject->methodCount();

        Shiboken::GilState gil;
        pySelf = (PyObject*)Shiboken::BindingManager::instance().retrieveWrapper(object);
        Q_ASSERT(pySelf);
        pp_name = PyString_FromString(mp.name());
        pp = Property::getObject(pySelf, pp_name);
        if (!pp) {
            qWarning("Invalid property: %s.", mp.name());
            Py_XDECREF(pp_name);
            return id - metaObject->methodCount();
        }
    }

    switch(call) {
#ifndef QT_NO_PROPERTIES
        case QMetaObject::ReadProperty:
        case QMetaObject::WriteProperty:
        case QMetaObject::ResetProperty:
        case QMetaObject::QueryPropertyDesignable:
        case QMetaObject::QueryPropertyScriptable:
        case QMetaObject::QueryPropertyStored:
        case QMetaObject::QueryPropertyEditable:
        case QMetaObject::QueryPropertyUser:
            pp->d->metaCallHandler(pp, pySelf, call, args);
            break;
#endif
        case QMetaObject::InvokeMetaMethod:
            id = callMethod(object, id, args);
            break;

        default:
            qWarning("Unsupported meta invocation type.");
    }

    if (call == QMetaObject::InvokeMetaMethod)
        id = id - metaObject->methodCount();
    else
        id = id - metaObject->propertyCount();

    if (pp || pp_name) {
        Shiboken::GilState gil;
        Py_XDECREF(pp);
        Py_XDECREF(pp_name);
    }
    return id;
}

static int PySide::callMethod(QObject* object, int id, void** args)
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
        PyObject* self = (PyObject*)Shiboken::BindingManager::instance().retrieveWrapper(object);
        PyObject* preparedArgs = NULL;
        Py_ssize_t args_size = paramTypes.count();

        if (args_size)
            preparedArgs = PyTuple_New(args_size);

        for (int i = 0, max = paramTypes.count(); i < max; ++i) {
            void* data = args[i+1];
            const char* dataType = paramTypes[i].constData();

            Shiboken::TypeResolver* tr = Shiboken::TypeResolver::get(dataType);
            if (tr) {
                PyObject* arg = tr->toPython(data);
                PyTuple_SET_ITEM(preparedArgs, i, arg);
            } else {
                PyErr_Format(PyExc_TypeError, "Can't call meta function because I have no idea how to handle %s", dataType);
                return -1;
            }
        }

        QString methodName = method.signature();
        methodName = methodName.left(methodName.indexOf('('));

        Shiboken::AutoDecRef pyMethod(PyObject_GetAttrString(self, qPrintable(methodName)));
        if (!pyMethod.isNull()) {
            Shiboken::AutoDecRef retval(PyObject_CallObject(pyMethod, preparedArgs));
            if (retval.isNull()) {
                qWarning() << "Error calling slot" << methodName;
                PyErr_Print();
            } else {
                const char* returnType = method.typeName();
                if (returnType && (strlen(returnType) > 0))
                    Shiboken::TypeResolver::get(returnType)->toCpp(retval, &args[0]);
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
        SbkObject* self = Shiboken::BindingManager::instance().retrieveWrapper(source);
        if (!Shiboken::Object::hasCppWrapper(self)) {
            qWarning() << "Invalid Signal signature:" << signature;
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

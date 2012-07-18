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
#include "dynamicqmetaobject.h"
#include "pysidemetafunction_p.h"

#include <QHash>
#include <QStringList>
#include <QMetaMethod>
#include <autodecref.h>
#include <gilstate.h>
#include <QDebug>
#include <limits>
#include <algorithm>
#include <typeresolver.h>
#include <basewrapper.h>
#include <sbkconverter.h>
#include <conversions.h>

#if QSLOT_CODE != 1 || QSIGNAL_CODE != 2
#error QSLOT_CODE and/or QSIGNAL_CODE changed! change the hardcoded stuff to the correct value!
#endif
#define PYSIDE_SLOT '1'
#define PYSIDE_SIGNAL '2'
#include "globalreceiverv2.h"
#include "globalreceiver.h"

#define PYTHON_TYPE "PyObject"

namespace {
    static PyObject *metaObjectAttr = 0;

    static int callMethod(QObject* object, int id, void** args);
    static PyObject* parseArguments(const QList< QByteArray >& paramTypes, void** args);
    static bool emitShortCircuitSignal(QObject* source, int signalIndex, PyObject* args);

#ifdef IS_PY3K
    static void destroyMetaObject(PyObject* obj)
    {
        delete reinterpret_cast<PySide::DynamicQMetaObject*>(PyCapsule_GetPointer(obj, 0));
    }

#else
    static void destroyMetaObject(void* obj)
    {
        delete reinterpret_cast<PySide::DynamicQMetaObject*>(obj);
    }
#endif
}

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

QDataStream &operator<<(QDataStream& out, const PyObjectWrapper& myObj)
{
    if (Py_IsInitialized() == 0) {
        qWarning() << "Stream operator for PyObject called without python interpreter.";
        return out;
    }

    static PyObject *reduce_func  = 0;

    Shiboken::GilState gil;
    if (!reduce_func) {
        Shiboken::AutoDecRef pickleModule(PyImport_ImportModule("pickle"));
        reduce_func = PyObject_GetAttrString(pickleModule, "dumps");
    }
    Shiboken::AutoDecRef repr(PyObject_CallFunctionObjArgs(reduce_func, (PyObject*)myObj, NULL));
    if (repr.object()) {
        const char* buff = 0;
        Py_ssize_t size  = 0;
        if (PyBytes_Check(repr.object())) {
            buff = PyBytes_AS_STRING(repr.object());
            size = PyBytes_GET_SIZE(repr.object());
        } else if (Shiboken::String::check(repr.object())) {
            buff = Shiboken::String::toCString(repr.object());
            size = Shiboken::String::len(repr.object());
        }
        QByteArray data(buff, size);
        out << data;
    }
    return out;
}

QDataStream &operator>>(QDataStream& in, PyObjectWrapper& myObj)
{
    if (Py_IsInitialized() == 0) {
        qWarning() << "Stream operator for PyObject called without python interpreter.";
        return in;
    }

    static PyObject *eval_func  = 0;

    Shiboken::GilState gil;
    if (!eval_func) {
        Shiboken::AutoDecRef pickleModule(PyImport_ImportModule("pickle"));
        eval_func = PyObject_GetAttrString(pickleModule, "loads");
    }

    QByteArray repr;
    in >> repr;
    Shiboken::AutoDecRef pyCode(PyBytes_FromStringAndSize(repr.data(), repr.size()));
    Shiboken::AutoDecRef value(PyObject_CallFunctionObjArgs(eval_func, pyCode.object(), 0));
    if (!value.object()) {
        value = Py_None;
    }
    myObj = PyObjectWrapper(value);
    return in;
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
    SharedMap m_globalReceivers;

    //Deprecated
    GlobalReceiver m_globalReceiver;

    SignalManagerPrivate()
    {
        m_globalReceivers = SharedMap( new QMap<QByteArray, GlobalReceiverV2*>() );
    }

    ~SignalManagerPrivate()
    {
        if (!m_globalReceivers.isNull()) {
            QList<GlobalReceiverV2*> values = m_globalReceivers->values();
            m_globalReceivers->clear();
            if (values.size()) {
                qDeleteAll(values);
            }
        }
    }
};

static void clearSignalManager()
{
    PySide::SignalManager::instance().clear();
}

static void PyObject_PythonToCpp_PyObject_PTR(PyObject* pyIn, void* cppOut)
{
    *((PyObject**)cppOut) = pyIn;
}
static PythonToCppFunc is_PyObject_PythonToCpp_PyObject_PTR_Convertible(PyObject* pyIn)
{
    return PyObject_PythonToCpp_PyObject_PTR;
}
static PyObject* PyObject_PTR_CppToPython_PyObject(const void* cppIn)
{
    PyObject* pyOut = (PyObject*)cppIn;
    if (pyOut)
        Py_INCREF(pyOut);
    return pyOut;
}

SignalManager::SignalManager() : m_d(new SignalManagerPrivate)
{
    // Register Qt primitive typedefs used on signals.
    using namespace Shiboken;

    // Register PyObject type to use in queued signal and slot connections
    qRegisterMetaType<PyObjectWrapper>(PYTHON_TYPE);
    qRegisterMetaTypeStreamOperators<PyObjectWrapper>(PYTHON_TYPE);
    qRegisterMetaTypeStreamOperators<PyObjectWrapper>("PyObjectWrapper");
    qRegisterMetaTypeStreamOperators<PyObjectWrapper>("PySide::PyObjectWrapper");

    SbkConverter* converter = Shiboken::Conversions::createConverter(&PyBaseObject_Type, 0);
    Shiboken::Conversions::setCppPointerToPythonFunction(converter, PyObject_PTR_CppToPython_PyObject);
    Shiboken::Conversions::setPythonToCppPointerFunctions(converter, PyObject_PythonToCpp_PyObject_PTR, is_PyObject_PythonToCpp_PyObject_PTR_Convertible);
    Shiboken::Conversions::registerConverterName(converter, PYTHON_TYPE);
    Shiboken::Conversions::registerConverterName(converter, "object");
    Shiboken::Conversions::registerConverterName(converter, "PyObjectWrapper");
    Shiboken::Conversions::registerConverterName(converter, "PySide::PyObjectWrapper");

    PySide::registerCleanupFunction(clearSignalManager);

    if (!metaObjectAttr)
        metaObjectAttr = Shiboken::String::fromCString("__METAOBJECT__");
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
    addGlobalSlotGetIndex(slot, callback);
}

int SignalManager::addGlobalSlotGetIndex(const char* slot, PyObject* callback)
{
    return m_d->m_globalReceiver.addSlot(slot, callback);
}

QObject* SignalManager::globalReceiver(QObject *sender, PyObject *callback)
{
    SharedMap globalReceivers = m_d->m_globalReceivers;
    QByteArray hash = GlobalReceiverV2::hash(callback);
    GlobalReceiverV2* gr = 0;
    if (!globalReceivers->contains(hash)) {
        gr = (*globalReceivers)[hash] = new GlobalReceiverV2(callback, globalReceivers);
        if (sender) {
            gr->incRef(sender); // create a link reference
            gr->decRef(); // remove extra reference
        }
    } else {
        gr = (*globalReceivers)[hash];
        if (sender)
            gr->incRef(sender);
    }

    return reinterpret_cast<QObject*>(gr);
}

int SignalManager::countConnectionsWith(const QObject *object)
{
    int count = 0;
    foreach(GlobalReceiverV2* g, m_d->m_globalReceivers->values()) {
        if (g->refCount(object))
            count++;
    }
    return count;
}

void SignalManager::notifyGlobalReceiver(QObject* receiver)
{
    reinterpret_cast<GlobalReceiverV2*>(receiver)->notify();
}

void SignalManager::releaseGlobalReceiver(const QObject* source, QObject* receiver)
{
    GlobalReceiverV2* gr = reinterpret_cast<GlobalReceiverV2*>(receiver);
    gr->decRef(source);
}

int SignalManager::globalReceiverSlotIndex(QObject* receiver, const char* signature) const
{
    return reinterpret_cast<GlobalReceiverV2*>(receiver)->addSlot(signature);
}

bool SignalManager::emitSignal(QObject* source, const char* signal, PyObject* args)
{
    if (!Signal::checkQtSignal(signal))
        return false;
    signal++;

    int signalIndex = source->metaObject()->indexOfSignal(signal);
    if (signalIndex != -1) {
        // cryptic but works!
        // if the signature doesn't have a '(' it's a shor circuited signal, i.e. std::find
        // returned the string null terminator.
        bool isShortCircuit = !*std::find(signal, signal + std::strlen(signal), '(');
        if (isShortCircuit)
            return emitShortCircuitSignal(source, signalIndex, args);
        else
            return MetaFunction::call(source, signalIndex, args);
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
    int methodCount = metaObject->methodCount();
    int propertyCount = metaObject->propertyCount();

    if (call != QMetaObject::InvokeMetaMethod) {
        mp = metaObject->property(id);
        if (!mp.isValid())
            return id - methodCount;

        Shiboken::GilState gil;
        pySelf = (PyObject*)Shiboken::BindingManager::instance().retrieveWrapper(object);
        Q_ASSERT(pySelf);
        pp_name = Shiboken::String::fromCString(mp.name());
        pp = Property::getObject(pySelf, pp_name);
        if (!pp) {
            qWarning("Invalid property: %s.", mp.name());
            Py_XDECREF(pp_name);
            return id - methodCount;
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

    // WARNING Isn't safe to call any metaObject and/or object methods beyond this point
    //         because the object can be deleted inside the called slot.

    if (call == QMetaObject::InvokeMetaMethod)
        id = id - methodCount;
    else
        id = id - propertyCount;

    if (pp || pp_name) {
        Shiboken::GilState gil;
        Py_XDECREF(pp);
        Py_XDECREF(pp_name);
    }
    return id;
}

int SignalManager::callPythonMetaMethod(const QMetaMethod& method, void** args, PyObject* pyMethod, bool isShortCuit)
{
    Q_ASSERT(pyMethod);

    Shiboken::GilState gil;
    PyObject* pyArguments = 0;

    if (isShortCuit)
        pyArguments = reinterpret_cast<PyObject*>(args[1]);
    else
        pyArguments = parseArguments(method.parameterTypes(), args);

    if (pyArguments) {
        Shiboken::Conversions::SpecificConverter* retConverter = NULL;
        const char* returnType = method.typeName();
        if (returnType && std::strcmp("", returnType)) {
            retConverter = new Shiboken::Conversions::SpecificConverter(returnType);
            if (!retConverter || !*retConverter) {
                PyErr_Format(PyExc_RuntimeError, "Can't find converter for '%s' to call Python meta method.", returnType);
                PyErr_Print();
                return -1;
            }
        }

        Shiboken::AutoDecRef retval(PyObject_CallObject(pyMethod, pyArguments));

        if (!isShortCuit && pyArguments)
            Py_DECREF(pyArguments);

        if (!retval.isNull() && retval != Py_None && !PyErr_Occurred() && retConverter)
            retConverter->toCpp(retval, args[0]);
        delete retConverter;
    }

    if (PyErr_Occurred())
        PyErr_Print();

    return -1;
}

bool SignalManager::registerMetaMethod(QObject* source, const char* signature, QMetaMethod::MethodType type)
{
    int ret = registerMetaMethodGetIndex(source, signature, type);
    return (ret != -1);
}

int SignalManager::registerMetaMethodGetIndex(QObject* source, const char* signature, QMetaMethod::MethodType type)
{
    Q_ASSERT(source);
    const QMetaObject* metaObject = source->metaObject();
    int methodIndex = metaObject->indexOfMethod(signature);
    // Create the dynamic signal is needed
    if (methodIndex == -1) {
        SbkObject* self = Shiboken::BindingManager::instance().retrieveWrapper(source);
        if (!Shiboken::Object::hasCppWrapper(self)) {
            qWarning() << "Invalid Signal signature:" << signature;
            return -1;
        } else {
            DynamicQMetaObject *dmo = 0;
            PyObject *pySelf = reinterpret_cast<PyObject*>(self);
            PyObject* dict = self->ob_dict;

            // Create a instance meta object
            if (!dict || !PyDict_Contains(dict, metaObjectAttr)) {
                dmo = new DynamicQMetaObject(pySelf->ob_type, metaObject);
#ifdef IS_PY3K
                PyObject* pyDmo = PyCapsule_New(dmo, 0, destroyMetaObject);
#else
                PyObject* pyDmo = PyCObject_FromVoidPtr(dmo, destroyMetaObject);
#endif

                PyObject_SetAttr(pySelf, metaObjectAttr, pyDmo);
                Py_DECREF(pyDmo);
            } else {
                dmo = reinterpret_cast<DynamicQMetaObject*>(const_cast<QMetaObject*>(metaObject));
            }

            if (type == QMetaMethod::Signal)
                return dmo->addSignal(signature);
            else
                return dmo->addSlot(signature);
        }
    }
    return methodIndex;
}

bool SignalManager::hasConnectionWith(const QObject *object)
{
    return m_d->m_globalReceiver.hasConnectionWith(object);
}

const QMetaObject* SignalManager::retriveMetaObject(PyObject *self)
{
    Shiboken::GilState gil;
    DynamicQMetaObject *mo = 0;
    Q_ASSERT(self);

    PyObject* dict = reinterpret_cast<SbkObject*>(self)->ob_dict;
    if (dict && PyDict_Contains(dict, metaObjectAttr)) {
        PyObject *pyMo = PyDict_GetItem(dict, metaObjectAttr);

#ifdef IS_PY3K
        mo = reinterpret_cast<DynamicQMetaObject*>(PyCapsule_GetPointer(pyMo, 0));
#else
        mo = reinterpret_cast<DynamicQMetaObject*>(PyCObject_AsVoidPtr(pyMo));
#endif
    } else {
        mo = reinterpret_cast<DynamicQMetaObject*>(Shiboken::Object::getTypeUserData(reinterpret_cast<SbkObject*>(self)));
    }

    mo->update();
    return mo;
}

namespace {

static int callMethod(QObject* object, int id, void** args)
{
    const QMetaObject* metaObject = object->metaObject();
    QMetaMethod method = metaObject->method(id);

    if (method.methodType() == QMetaMethod::Signal) {
        // emit python signal
        QMetaObject::activate(object, id, args);
    } else {
        Shiboken::GilState gil;
        PyObject* self = (PyObject*)Shiboken::BindingManager::instance().retrieveWrapper(object);
        QByteArray methodName = method.signature();
        methodName = methodName.left(methodName.indexOf('('));
        Shiboken::AutoDecRef pyMethod(PyObject_GetAttrString(self, methodName));
        SignalManager::callPythonMetaMethod(method, args, pyMethod, false);
    }
    return -1;
}


static PyObject* parseArguments(const QList<QByteArray>& paramTypes, void** args)
{
    int argsSize = paramTypes.count();
    PyObject* preparedArgs = PyTuple_New(argsSize);

    for (int i = 0, max = argsSize; i < max; ++i) {
        void* data = args[i+1];
        const char* dataType = paramTypes[i].constData();
        Shiboken::Conversions::SpecificConverter converter(dataType);
        if (converter) {
            PyTuple_SET_ITEM(preparedArgs, i, converter.toPython(data));
        } else {
            PyErr_Format(PyExc_TypeError, "Can't call meta function because I have no idea how to handle %s", dataType);
            Py_DECREF(preparedArgs);
            return 0;
        }
    }
    return preparedArgs;
}

static bool emitShortCircuitSignal(QObject* source, int signalIndex, PyObject* args)
{
    void* signalArgs[2] = {0, args};
    source->qt_metacall(QMetaObject::InvokeMetaMethod, signalIndex, signalArgs);
    return true;
}

} //namespace

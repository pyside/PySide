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

#include "pyside.h"
#include "signalmanager.h"
#include "pysideclassinfo_p.h"
#include "pysideproperty_p.h"
#include "pysideproperty.h"
#include "pysidesignal.h"
#include "pysidesignal_p.h"
#include "pysideslot_p.h"
#include "pysidemetafunction_p.h"
#include "pysidemetafunction.h"
#include "dynamicqmetaobject.h"

#include <basewrapper.h>
#include <conversions.h>
#include <typeresolver.h>
#include <bindingmanager.h>
#include <algorithm>
#include <cctype>
#include <QStack>
#include <QCoreApplication>

static QStack<PySide::CleanupFunction> cleanupFunctionList;

namespace PySide
{

void init(PyObject *module)
{
    ClassInfo::init(module);
    Signal::init(module);
    Slot::init(module);
    Property::init(module);
    MetaFunction::init(module);
    // Init signal manager, so it will register some meta types used by QVariant.
    SignalManager::instance();
}

bool fillQtProperties(PyObject* qObj, const QMetaObject* metaObj, PyObject* kwds, const char** blackList, unsigned int blackListSize)
{

    PyObject *key, *value;
    Py_ssize_t pos = 0;

    while (PyDict_Next(kwds, &pos, &key, &value)) {
        if (!blackListSize || !std::binary_search(blackList, blackList + blackListSize, std::string(PyString_AS_STRING(key)))) {
            QByteArray propName(PyString_AS_STRING(key));
            if (metaObj->indexOfProperty(propName) != -1) {
                propName[0] = std::toupper(propName[0]);
                propName.prepend("set");

                Shiboken::AutoDecRef propSetter(PyObject_GetAttrString(qObj, propName.constData()));
                if (!propSetter.isNull()) {
                    Shiboken::AutoDecRef args(PyTuple_Pack(1, value));
                    Shiboken::AutoDecRef retval(PyObject_CallObject(propSetter, args));
                } else {
                    PyObject* attr = PyObject_GenericGetAttr(qObj, key);
                    if (PySide::Property::isPropertyType(attr))
                        PySide::Property::setValue(reinterpret_cast<PySideProperty*>(attr), qObj, value);
                }
            } else {
                propName.append("()");
                if (metaObj->indexOfSignal(propName) != -1) {
                    propName.prepend('2');
                    PySide::Signal::connect(qObj, propName, value);
                } else {
                    PyErr_Format(PyExc_AttributeError, "'%s' is not a Qt property or a signal", propName.constData());
                    return false;
                };
            }
        }
    }
    return true;
}

void registerCleanupFunction(CleanupFunction func)
{
    cleanupFunctionList.push(func);
}

void runCleanupFunctions()
{
    while (!cleanupFunctionList.isEmpty()) {
        CleanupFunction f = cleanupFunctionList.pop();
        f();
    }
}

static void destructionVisitor(SbkObject* pyObj, void* data)
{
    void** realData = reinterpret_cast<void**>(data);
    SbkObject* pyQApp = reinterpret_cast<SbkObject*>(realData[0]);
    PyTypeObject* pyQObjectType = reinterpret_cast<PyTypeObject*>(realData[1]);

    if (pyObj != pyQApp && PyObject_TypeCheck(pyObj, pyQObjectType)) {
        if (Shiboken::Object::hasOwnership(pyObj) && Shiboken::Object::isValid(pyObj, false)) {
            Shiboken::Object::setValidCpp(pyObj, false);

            Py_BEGIN_ALLOW_THREADS
            Shiboken::callCppDestructor<QObject>(Shiboken::Object::cppPointer(pyObj, pyQObjectType));
            Py_END_ALLOW_THREADS
        }
    }
};

void destroyQCoreApplication()
{
    SignalManager::instance().clear();
    QCoreApplication* app = QCoreApplication::instance();
    if (!app)
        return;

    Shiboken::BindingManager& bm = Shiboken::BindingManager::instance();
    SbkObject* pyQApp = bm.retrieveWrapper(app);
    PyTypeObject* pyQObjectType = Shiboken::TypeResolver::get("QObject*")->pythonType();
    assert(pyQObjectType);

    void* data[2] = {pyQApp, pyQObjectType};
    bm.visitAllPyObjects(&destructionVisitor, &data);

    // in the end destroy app
    delete app;
}

void initDynamicMetaObject(SbkObjectType* type, const QMetaObject* base)
{
    QByteArray typeName = QByteArray(type->super.ht_type.tp_name).split('.').last();
    DynamicQMetaObject* mo = new PySide::DynamicQMetaObject(typeName, base);
    Shiboken::ObjectType::setTypeUserData(type, mo, &Shiboken::callCppDestructor<DynamicQMetaObject>);
}

void initQObjectSubType(SbkObjectType* type, PyObject* args, PyObject* kwds)
{
    PyTypeObject* qObjType = Shiboken::TypeResolver::get("QObject*")->pythonType();
    QByteArray className(PyString_AS_STRING(PyTuple_GET_ITEM(args, 0)));

    PyObject* bases = PyTuple_GET_ITEM(args, 1);
    int numBases = PyTuple_GET_SIZE(bases);
    QMetaObject* baseMo = 0;

    for (int i = 0; i < numBases; ++i) {
        PyTypeObject* base = reinterpret_cast<PyTypeObject*>(PyTuple_GET_ITEM(bases, i));
        if (PyType_IsSubtype(base, qObjType)) {
            baseMo = reinterpret_cast<QMetaObject*>(Shiboken::ObjectType::getTypeUserData(reinterpret_cast<SbkObjectType*>(base)));
            // If it's a class like QObject, QWidget, etc, use the original QMetaObject instead of the dynamic one
            // IMO this if is a bug, however it keeps the current behaviour.
            if (!Shiboken::ObjectType::isUserType(base))
                baseMo = const_cast<QMetaObject*>(baseMo->d.superdata);
            break;
        }
    }
    if (!baseMo) {
        qWarning("Sub class of QObject not inheriting QObject!? Crash will happen when using %s.", className.constData());
        return;
    }

    DynamicQMetaObject* mo = new PySide::DynamicQMetaObject(className.constData(), baseMo);

    Shiboken::ObjectType::setTypeUserData(type, mo, &Shiboken::callCppDestructor<DynamicQMetaObject>);

    PyObject* attrs = PyTuple_GET_ITEM(args, 2);
    PyObject* key;
    PyObject* value;
    Py_ssize_t pos = 0;

    typedef std::pair<const char*, PyObject*> PropPair;
    QList<PropPair> properties;

    Shiboken::AutoDecRef slotAttrName(PyString_FromString(PYSIDE_SLOT_LIST_ATTR));

    while (PyDict_Next(attrs, &pos, &key, &value)) {
        if (Property::checkType(value)) {
            // Leave the properties to be register after signals because they may depend on notify signals
            properties << PropPair(PyString_AS_STRING(key), value);
        } else if (Signal::checkType(value)) { // Register signals
            PySideSignal* data = reinterpret_cast<PySideSignal*>(value);
            const char* signalName = PyString_AS_STRING(key);
            data->signalName = strdup(signalName);
            QByteArray sig;
            sig.reserve(128);
            for (int i = 0; i < data->signaturesSize; ++i) {
                sig = signalName;
                sig += '(';
                if (data->signatures[i])
                    sig += data->signatures[i];
                sig += ')';
                if (baseMo->indexOfSignal(sig) == -1)
                    mo->addSignal(sig);
            }
        } else if (PyFunction_Check(value)) { // Register slots
            if (PyObject_HasAttr(value, slotAttrName)) {
                PyObject* signatureList = PyObject_GetAttr(value, slotAttrName);
                for(Py_ssize_t i = 0, i_max = PyList_Size(signatureList); i < i_max; ++i) {
                    PyObject* signature = PyList_GET_ITEM(signatureList, i);
                    QByteArray sig(PyString_AS_STRING(signature));
                    //slot the slot type and signature
                    QList<QByteArray> slotInfo = sig.split(' ');
                    int index = baseMo->indexOfSlot(slotInfo[1]);
                    if (index == -1)
                        mo->addSlot(slotInfo[1], slotInfo[0]);
                }
            }
        }
    }

    // Register properties
    foreach (PropPair propPair, properties)
        mo->addProperty(propPair.first, propPair.second);
}

PyObject* getMetaDataFromQObject(QObject* cppSelf, PyObject* self, PyObject* name)
{
    PyObject* attr = PyObject_GenericGetAttr(self, name);
    if (!Shiboken::Object::isValid(reinterpret_cast<SbkObject*>(self), false))
        return attr;

    if (attr && Property::isPropertyType(attr)) {
        PyObject *value = Property::getValue(reinterpret_cast<PySideProperty*>(attr), self);
        if (!value)
            return 0;
        Py_DECREF(attr);
        Py_INCREF(value);
        attr = value;
    }

    //mutate native signals to signal instance type
    if (attr && PyObject_TypeCheck(attr, &PySideSignalType)) {
        PyObject* signal = reinterpret_cast<PyObject*>(Signal::initialize(reinterpret_cast<PySideSignal*>(attr), name, self));
        PyObject_SetAttr(self, name, reinterpret_cast<PyObject*>(signal));
        return signal;
    }

    //search on metaobject (avoid internal attributes started with '__')
    if (!attr && !QString(PyString_AS_STRING(name)).startsWith("__")) {
        const QMetaObject* metaObject = cppSelf->metaObject();
        QByteArray cname(PyString_AS_STRING(name));
        cname += '(';
        //signal
        QList<QMetaMethod> signalList;
        for(int i=0, i_max = metaObject->methodCount(); i < i_max; i++) {
            QMetaMethod method = metaObject->method(i);
            if (QString(method.signature()).startsWith(cname)) {
                if (method.methodType() == QMetaMethod::Signal) {
                    signalList.append(method);
                } else {
                    PySideMetaFunction* func = MetaFunction::newObject(cppSelf, i);
                    if (func) {
                        PyObject_SetAttr(self, name, (PyObject*)func);
                        return (PyObject*)func;
                    }
                }
            }
        }
        if (signalList.size() > 0) {
            PyObject* pySignal = reinterpret_cast<PyObject*>(Signal::newObjectFromMethod(self, signalList));
            PyObject_SetAttr(self, name, pySignal);
            return pySignal;
        }
    }
    return attr;
}

} //namespace PySide


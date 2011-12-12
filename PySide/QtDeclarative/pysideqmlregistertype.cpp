/*
 * This file is part of the Shiboken Python Bindings Generator project.
 *
 * Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
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

#include "pysideqmlregistertype.h"
// Qt
#include <QObject>
#include <QDeclarativeEngine>
#include <QMutex>
// shiboken
#include <typeresolver.h>
#include <gilstate.h>
#include <sbkdbg.h>
// pyside
#include <pyside.h>
#include <dynamicqmetaobject.h>
#include <pysideproperty.h>

// auto generated headers
#include "qdeclarativeitem_wrapper.h"
#include "pyside_qtcore_python.h"
#include "pyside_qtdeclarative_python.h"

#ifndef PYSIDE_MAX_QML_TYPES
// Maximum number of different types the user cna export to QML using qmlRegisterType.
#define PYSIDE_MAX_QML_TYPES 50
#endif

// Forward declarations
static void propListMetaCall(PySideProperty* pp, PyObject* self, QMetaObject::Call call, void** args);


// All registered python types
static PyObject* pyTypes[PYSIDE_MAX_QML_TYPES];
static void (*createFuncs[PYSIDE_MAX_QML_TYPES])(void*);

// Mutex used to avoid race condition on PySide::nextQObjectMemoryAddr
static QMutex nextQmlElementMutex;

template<int N>
struct ElementFactoryBase
{
    static void createInto(void* memory)
    {
        QMutexLocker locker(&nextQmlElementMutex);
        PySide::setNextQObjectMemoryAddr(memory);
        Shiboken::GilState state;
        PyObject* obj = PyObject_CallObject(pyTypes[N], 0);
        if (!obj || PyErr_Occurred())
            PyErr_Print();
        PySide::setNextQObjectMemoryAddr(0);
    }
};

template<int N>
struct ElementFactory : ElementFactoryBase<N>
{
    static void init()
    {
        createFuncs[N] = &ElementFactoryBase<N>::createInto;
        ElementFactory<N-1>::init();
    }
};

template<>
struct  ElementFactory<0> : ElementFactoryBase<0>
{
    static void init()
    {
        createFuncs[0] = &ElementFactoryBase<0>::createInto;
    }
};

int PySide::qmlRegisterType(PyObject* pyObj, const char* uri, int versionMajor, int versionMinor, const char* qmlName)
{
    using namespace Shiboken;

    static PyTypeObject* qobjectType = Shiboken::Conversions::getPythonTypeObject("QObject*");
    static PyTypeObject* qdeclarativeType = Shiboken::Conversions::getPythonTypeObject("QDeclarativeItem*");
    assert(qobjectType);
    static int nextType = 0;

    if (nextType >= PYSIDE_MAX_QML_TYPES) {
        PyErr_Format(PyExc_TypeError, "QML doesn't really like language bindings, so you can only export %d types to QML.", PYSIDE_MAX_QML_TYPES);
        return -1;
    }

    if (!PySequence_Contains(((PyTypeObject*)pyObj)->tp_mro, (PyObject*)qobjectType)) {
        PyErr_Format(PyExc_TypeError, "A type inherited from %s expected, got %s.", qobjectType->tp_name, ((PyTypeObject*)pyObj)->tp_name);
        return -1;
    }

    bool isDeclarativeType = PySequence_Contains(((PyTypeObject*)pyObj)->tp_mro, (PyObject*)qdeclarativeType);

    QMetaObject* metaObject = reinterpret_cast<QMetaObject*>(ObjectType::getTypeUserData(reinterpret_cast<SbkObjectType*>(pyObj)));
    Q_ASSERT(metaObject);

    // Inc ref the type object, don't worry about dec ref them because there's no way to unregister a QML type
    Py_INCREF(pyObj);

    // All ready... now the ugly code begins... :-)
    pyTypes[nextType] = pyObj;

    // Init proxy object static meta object
    QDeclarativePrivate::RegisterType type;
    type.version = 0;
    if (isDeclarativeType) {
        type.typeId = qMetaTypeId<QDeclarativeItem*>();
        type.listId = qMetaTypeId<QDeclarativeListProperty<QDeclarativeItem> >();

        type.attachedPropertiesFunction = QDeclarativePrivate::attachedPropertiesFunc<QDeclarativeItem>();
        type.attachedPropertiesMetaObject = QDeclarativePrivate::attachedPropertiesMetaObject<QDeclarativeItem>();

        type.parserStatusCast = QDeclarativePrivate::StaticCastSelector<QDeclarativeItem, QDeclarativeParserStatus>::cast();
        type.valueSourceCast = QDeclarativePrivate::StaticCastSelector<QDeclarativeItem, QDeclarativePropertyValueSource>::cast();
        type.valueInterceptorCast = QDeclarativePrivate::StaticCastSelector<QDeclarativeItem, QDeclarativePropertyValueInterceptor>::cast();
    } else {
        type.typeId = qMetaTypeId<QObject*>();
        type.listId = qMetaTypeId<QDeclarativeListProperty<QObject> >();
        type.attachedPropertiesFunction = QDeclarativePrivate::attachedPropertiesFunc<QObject>();
        type.attachedPropertiesMetaObject = QDeclarativePrivate::attachedPropertiesMetaObject<QObject>();

        type.parserStatusCast = QDeclarativePrivate::StaticCastSelector<QObject, QDeclarativeParserStatus>::cast();
        type.valueSourceCast = QDeclarativePrivate::StaticCastSelector<QObject, QDeclarativePropertyValueSource>::cast();
        type.valueInterceptorCast = QDeclarativePrivate::StaticCastSelector<QObject, QDeclarativePropertyValueInterceptor>::cast();
    }
    type.objectSize = PySide::getSizeOfQObject(reinterpret_cast<SbkObjectType*>(pyObj));
    type.create = createFuncs[nextType];
    type.uri = uri;
    type.versionMajor = versionMajor;
    type.versionMinor = versionMinor;
    type.elementName = qmlName;
    type.metaObject = metaObject;

    type.extensionObjectCreate = 0;
    type.extensionMetaObject = 0;
    type.customParser = 0;

    int qmlTypeId = QDeclarativePrivate::qmlregister(QDeclarativePrivate::TypeRegistration, &type);
    ++nextType;
    return qmlTypeId;
}

extern "C"
{

// This is the user data we store in the property.
struct DeclarativeListProperty
{
    PyTypeObject* type;
    PyObject* append;
    PyObject* at;
    PyObject* clear;
    PyObject* count;
};

static int propListTpInit(PyObject* self, PyObject* args, PyObject* kwds)
{
    static const char *kwlist[] = {"type", "append", "at", "clear", "count", 0};
    PySideProperty* pySelf = reinterpret_cast<PySideProperty*>(self);
    DeclarativeListProperty* data = new DeclarativeListProperty;
    memset(data, 0, sizeof(DeclarativeListProperty));

    if (!PyArg_ParseTupleAndKeywords(args, kwds,
                                     "OO|OOO:QtDeclarative.ListProperty", (char**) kwlist,
                                     &data->type,
                                     &data->append,
                                     &data->at,
                                     &data->clear,
                                     &data->count)) {
        return 0;
    }
    PySide::Property::setMetaCallHandler(pySelf, &propListMetaCall);
    PySide::Property::setTypeName(pySelf, "QDeclarativeListProperty<QDeclarativeItem>");
    PySide::Property::setUserData(pySelf, data);

    return 1;
}

void propListTpFree(void* self)
{
    PySideProperty* pySelf = reinterpret_cast<PySideProperty*>(self);
    delete reinterpret_cast<DeclarativeListProperty*>(PySide::Property::userData(pySelf));
    // calls base type constructor
    Py_TYPE(pySelf)->tp_base->tp_free(self);
}

PyTypeObject PropertyListType = {
    PyVarObject_HEAD_INIT(0, 0)
    "ListProperty",            /*tp_name*/
    sizeof(PySideProperty),    /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    0,                         /*tp_dealloc*/
    0,                         /*tp_print*/
    0,                         /*tp_getattr*/
    0,                         /*tp_setattr*/
    0,                         /*tp_compare*/
    0,                         /*tp_repr*/
    0,                         /*tp_as_number*/
    0,                         /*tp_as_sequence*/
    0,                         /*tp_as_mapping*/
    0,                         /*tp_hash */
    0,                         /*tp_call*/
    0,                         /*tp_str*/
    0,                         /*tp_getattro*/
    0,                         /*tp_setattro*/
    0,                         /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT,        /*tp_flags*/
    0,                         /*tp_doc */
    0,                         /*tp_traverse */
    0,                         /*tp_clear */
    0,                         /*tp_richcompare */
    0,                         /*tp_weaklistoffset */
    0,                         /*tp_iter */
    0,                         /*tp_iternext */
    0,                         /*tp_methods */
    0,                         /*tp_members */
    0,                         /*tp_getset */
    &PySidePropertyType,       /*tp_base */
    0,                         /*tp_dict */
    0,                         /*tp_descr_get */
    0,                         /*tp_descr_set */
    0,                         /*tp_dictoffset */
    propListTpInit,            /*tp_init */
    0,                         /*tp_alloc */
    0,                         /*tp_new */
    propListTpFree,            /*tp_free */
    0,                         /*tp_is_gc */
    0,                         /*tp_bases */
    0,                         /*tp_mro */
    0,                         /*tp_cache */
    0,                         /*tp_subclasses */
    0,                         /*tp_weaklist */
    0,                         /*tp_del */
};

} // extern "C"

// Implementation of QDeclarativeListProperty<T>::AppendFunction callback
void propListAppender(QDeclarativeListProperty<QDeclarativeItem>* propList, QDeclarativeItem* item)
{
    Shiboken::GilState state;

    Shiboken::AutoDecRef args(PyTuple_New(2));
    PyTuple_SET_ITEM(args, 0, Shiboken::Conversions::pointerToPython((SbkObjectType*)SbkPySide_QtCoreTypes[SBK_QOBJECT_IDX], propList->object));
    PyTuple_SET_ITEM(args, 1, Shiboken::Conversions::pointerToPython((SbkObjectType*)SbkPySide_QtDeclarativeTypes[SBK_QDECLARATIVEITEM_IDX], item));

    DeclarativeListProperty* data = reinterpret_cast<DeclarativeListProperty*>(propList->data);
    Shiboken::AutoDecRef retVal(PyObject_CallObject(data->append, args));

    if (PyErr_Occurred())
        PyErr_Print();
}

// Implementation of QDeclarativeListProperty<T>::CountFunction callback
int propListCount(QDeclarativeListProperty<QDeclarativeItem>* propList)
{
    Shiboken::GilState state;

    Shiboken::AutoDecRef args(PyTuple_New(1));
    PyTuple_SET_ITEM(args, 0, Shiboken::Conversions::pointerToPython((SbkObjectType*)SbkPySide_QtCoreTypes[SBK_QOBJECT_IDX], propList->object));

    DeclarativeListProperty* data = reinterpret_cast<DeclarativeListProperty*>(propList->data);
    Shiboken::AutoDecRef retVal(PyObject_CallObject(data->count, args));

    // Check return type
    int cppResult = 0;
    PythonToCppFunc pythonToCpp;
    if (PyErr_Occurred())
        PyErr_Print();
    else if ((pythonToCpp = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<int>(), retVal)))
        pythonToCpp(retVal, &cppResult);
    return cppResult;
}

// Implementation of QDeclarativeListProperty<T>::AtFunction callback
QDeclarativeItem* propListAt(QDeclarativeListProperty<QDeclarativeItem>* propList, int index)
{
    Shiboken::GilState state;

    Shiboken::AutoDecRef args(PyTuple_New(2));
    PyTuple_SET_ITEM(args, 0, Shiboken::Conversions::pointerToPython((SbkObjectType*)SbkPySide_QtCoreTypes[SBK_QOBJECT_IDX], propList->object));
    PyTuple_SET_ITEM(args, 1, Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<int>(), &index));

    DeclarativeListProperty* data = reinterpret_cast<DeclarativeListProperty*>(propList->data);
    Shiboken::AutoDecRef retVal(PyObject_CallObject(data->at, args));

    QDeclarativeItem* result = 0;
    if (PyErr_Occurred())
        PyErr_Print();
    else if (PyType_IsSubtype(Py_TYPE(retVal), data->type))
        Shiboken::Conversions::pythonToCppPointer((SbkObjectType*)SbkPySide_QtCoreTypes[SBK_QDECLARATIVEITEM_IDX], retVal, &result);
    return result;
}

// Implementation of QDeclarativeListProperty<T>::ClearFunction callback
void propListClear(QDeclarativeListProperty<QDeclarativeItem>* propList)
{
    Shiboken::GilState state;

    Shiboken::AutoDecRef args(PyTuple_New(1));
    PyTuple_SET_ITEM(args, 0, Shiboken::Conversions::pointerToPython((SbkObjectType*)SbkPySide_QtCoreTypes[SBK_QOBJECT_IDX], propList->object));

    DeclarativeListProperty* data = reinterpret_cast<DeclarativeListProperty*>(propList->data);
    Shiboken::AutoDecRef retVal(PyObject_CallObject(data->clear, args));

    if (PyErr_Occurred())
        PyErr_Print();
}

// qt_metacall specialization for ListProperties
static void propListMetaCall(PySideProperty* pp, PyObject* self, QMetaObject::Call call, void** args)
{
    if (call != QMetaObject::ReadProperty)
        return;

    DeclarativeListProperty* data = reinterpret_cast<DeclarativeListProperty*>(PySide::Property::userData(pp));
    QObject* qobj;
    Shiboken::Conversions::pythonToCppPointer((SbkObjectType*)SbkPySide_QtCoreTypes[SBK_QOBJECT_IDX], self, &qobj);
    QDeclarativeListProperty<QDeclarativeItem> declProp(qobj, data, &propListAppender);

    if (data->count)
        declProp.count = &propListCount;
    if (data->at)
        declProp.at = &propListAt;
    if (data->clear)
        declProp.clear = &propListClear;

    // Copy the data to the memory location requested by the meta call
    void* v = args[0];
    *reinterpret_cast<QDeclarativeListProperty<QDeclarativeItem>*>(v) = declProp;
}


void PySide::initQmlSupport(PyObject* module)
{
    ElementFactory<PYSIDE_MAX_QML_TYPES - 1>::init();

    // Export DeclarativeListProperty type
    if (PyType_Ready(&PropertyListType) < 0)
        return;

    Py_INCREF((PyObject*)&PropertyListType);
    PyModule_AddObject(module, PropertyListType.tp_name, (PyObject*)&PropertyListType);

}



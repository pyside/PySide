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
#include <Python.h>
#include <QObject>
#include <QDeclarativeEngine>
#include <QMutex>
#include <typeresolver.h>
#include "qdeclarativeitem_wrapper.h"
#include <sbkdbg.h>

#ifndef PYSIDE_MAX_QML_TYPES
// Maximum number of different types the user cna export to QML using qmlRegisterType.
#define PYSIDE_MAX_QML_TYPES 50
#endif

// All registered python types
static PyObject* pyTypes[PYSIDE_MAX_QML_TYPES];
static void (*createFuncs[PYSIDE_MAX_QML_TYPES])(void*);

/// QDeclarativeItem will create objects using placement new then this pointer is non-null.
void* PySide::nextQmlElementMemoryAddr = 0;
// Mutex used to avoid race condition on PySide::nextQmlElementMemoryAddr
static QMutex nextQmlElementMutex;

template<int N>
struct ElementFactoryBase
{
    static void createInto(void* memory)
    {
        QMutexLocker locker(&nextQmlElementMutex);
        PySide::nextQmlElementMemoryAddr = memory;
        PyObject* obj = PyObject_CallObject(pyTypes[N], 0);
        if (!obj || PyErr_Occurred())
            PyErr_Print();
        PySide::nextQmlElementMemoryAddr = 0;
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

void PySide::initQmlSupport()
{
    ElementFactory<PYSIDE_MAX_QML_TYPES - 1>::init();
}

int PySide::qmlRegisterType(PyObject* pyObj, const char* uri, int versionMajor, int versionMinor, const char* qmlName)
{
    using namespace Shiboken;

    static PyTypeObject* declarativeItemType = TypeResolver::get("QDeclarativeItem*")->pythonType();
    assert(declarativeItemType);
    static int nextType = 0;

    if (nextType >= PYSIDE_MAX_QML_TYPES) {
        PyErr_Format(PyExc_TypeError, "QML doesn't really like language bindings, so you can only export %d types to QML.", PYSIDE_MAX_QML_TYPES);
        return -1;
    }

    if (pyObj->ob_type != &SbkObjectType_Type) {
        PyErr_Format(PyExc_TypeError, "A shiboken-based python type expected, got %s.", pyObj->ob_type->tp_name);
        return -1;
    }

    if (!PySequence_Contains(((PyTypeObject*)pyObj)->tp_mro, (PyObject*)declarativeItemType)) {
        PyErr_Format(PyExc_TypeError, "A type inherited from %s expected, got %s.", declarativeItemType->tp_name, ((PyTypeObject*)pyObj)->tp_name);
        return -1;
    }

    QMetaObject* metaObject = reinterpret_cast<QMetaObject*>(ObjectType::getTypeUserData(reinterpret_cast<SbkObjectType*>(pyObj)));
    Q_ASSERT(metaObject);

    // All ready... now the ugly code begins... :-)
    pyTypes[nextType] = pyObj;

    // Init proxy object static meta object
    QDeclarativePrivate::RegisterType type;
    type.version = 0;
    type.typeId = qMetaTypeId<QDeclarativeItem*>();
    type.listId = qMetaTypeId<QDeclarativeListProperty<QDeclarativeItem> >();
    type.objectSize = sizeof(QDeclarativeItemWrapper);
    type.create = createFuncs[nextType];
    type.uri = uri;
    type.versionMajor = versionMajor;
    type.versionMinor = versionMinor;
    type.elementName = qmlName;
    type.metaObject = metaObject;

    type.attachedPropertiesFunction = QDeclarativePrivate::attachedPropertiesFunc<QDeclarativeItem>();
    type.attachedPropertiesMetaObject = QDeclarativePrivate::attachedPropertiesMetaObject<QDeclarativeItem>();

    type.parserStatusCast = QDeclarativePrivate::StaticCastSelector<QDeclarativeItem,QDeclarativeParserStatus>::cast();
    type.valueSourceCast = QDeclarativePrivate::StaticCastSelector<QDeclarativeItem,QDeclarativePropertyValueSource>::cast();
    type.valueInterceptorCast = QDeclarativePrivate::StaticCastSelector<QDeclarativeItem,QDeclarativePropertyValueInterceptor>::cast();

    type.extensionObjectCreate = 0;
    type.extensionMetaObject = 0;
    type.customParser = 0;

    int qmlTypeId = QDeclarativePrivate::qmlregister(QDeclarativePrivate::TypeRegistration, &type);
    ++nextType;
    return qmlTypeId;
}

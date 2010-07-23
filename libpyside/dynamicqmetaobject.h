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

#ifndef DYNAMICQMETAOBJECT_H
#define DYNAMICQMETAOBJECT_H

#include "pysidemacros.h"
#include <Python.h>
#include <QMetaObject>
#include <QLinkedList>
#include <QByteArray>
#include <QSharedPointer>

#define PYSIDE_SLOT_LIST_ATTR "_slots"

class QObject;

namespace PySide
{

class MethodData
{
public:
    MethodData(){}
    MethodData(const char* signature, const char* type);
    void clear();
    bool isValid() const;
    QByteArray signature() const;
    QByteArray type() const;
    bool operator==(const MethodData& other) const;
    bool operator==(const char* other) const;

private:
    QSharedPointer<QByteArray> m_signature;
    QSharedPointer<QByteArray> m_type;
};

class PropertyData
{
public:
    PropertyData();
    PropertyData(const char*name, PyObject *data);
    QByteArray name() const;
    QByteArray type() const;
    uint flags() const;
    bool isValid() const;
    bool operator==(const PropertyData& other) const;
    bool operator==(const char* name) const;

private:
    QByteArray m_name;
    PyObject* m_data;
};

class PYSIDE_API DynamicQMetaObject : public QMetaObject
{
public:
    DynamicQMetaObject(const char* className, const QMetaObject* metaObject);
    ~DynamicQMetaObject();

    void addSignal(const char* signal, const char* type=0);
    void addSlot(const char* slot, const char* type=0);
    void addProperty(const char* property, PyObject* data);

    void removeSignal(uint idex);
    void removeSlot(uint index);
    void removeProperty(uint index);

    //Retrieve Python metadata to create QMetaObject (class name, signals, slot)
    static DynamicQMetaObject* createBasedOn(PyObject* obj, PyTypeObject* type, const QMetaObject* base);

private:
    QLinkedList<MethodData> m_signals;
    QLinkedList<MethodData> m_slots;
    QLinkedList<PropertyData> m_properties;
    QByteArray m_className;

    void updateMetaObject();
    void writeMethodsData(QLinkedList<MethodData>& methods, unsigned int **data, QList<QByteArray> *strings, int *index, int max_count, int null_index, int flags);
};

PYSIDE_API inline void deleteDynamicQMetaObject(void* data)
{
    delete reinterpret_cast<DynamicQMetaObject*>(data);
}

}
#endif

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

#ifndef DYNAMICQMETAOBJECT_H
#define DYNAMICQMETAOBJECT_H

#include "pysidemacros.h"
#include <Python.h>
#include <QMetaObject>

namespace PySide
{

class DynamicQMetaObject : public QMetaObject
{
public:
    DynamicQMetaObject(const char* className, const QMetaObject* metaObject);
    ~DynamicQMetaObject();

    void addSignal(const char* signal, const char* type = 0);
    void addSlot(const char* slot, const char* type = 0);
    void addProperty(const char* property, PyObject* data);

    void removeSignal(uint idex);
    void removeSlot(uint index);
    void removeProperty(uint index);

private:
    class DynamicQMetaObjectPrivate;
    DynamicQMetaObjectPrivate* m_d;
};

}
#endif

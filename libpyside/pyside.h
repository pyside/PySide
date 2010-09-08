/*
 * This file is part of the Shiboken Python Bindings Generator project.
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

#ifndef PYSIDE_H
#define PYSIDE_H

#include <Python.h>
#include <pysidemacros.h>
#include <QMetaType>

namespace PySide
{

PYSIDE_API void init(PyObject *module);

/**
 * Hash function used to enable hash on objects not supported on native Qt library which has toString function.
 */
template<class T>
inline uint hash(const T& value)
{
    return qHash(value.toString());
}

/**
*   If the type \p T was registered on Qt meta type system with Q_DECLARE_METATYPE macro, this class will initialize
*   the meta type.
*
*   Initialize a meta type means register it on Qt meta type system, Qt itself only do this on the first call of
*   qMetaTypeId, and this is exactly what we do to init it. If we don't do that, calls to QMetaType::type("QMatrix2x2")
*   could return zero, causing QVariant to not recognize some C++ types, like QMatrix2x2.
*/
template<typename T, bool OK = QMetaTypeId<T>::Defined >
struct initQtMetaType {
    initQtMetaType()
    {
        qMetaTypeId<T>();
    }
};

// Template specialization to do nothing when the type wasn't registered on Qt meta type system.
template<typename T>
struct initQtMetaType<T, false> {
};

} //namespace PySide


#endif // PYSIDE_H


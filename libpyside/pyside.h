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

#ifndef PYSIDE_H
#define PYSIDE_H

#include <Python.h>
#include <pysidemacros.h>
#include <QMetaType>
#include <QHash>
#include <QList>

class SbkObjectType;

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
 * Fill QObject properties and do signal connections using the values found in \p kwds dictonary.
 * \param qObj PyObject fot the QObject.
 * \param metaObj QMetaObject of \p qObj.
 * \param blackList keys to be ignored in kwds dictionary, this string list MUST be sorted.
 * \param blackListSize numbe rof elements in blackList.
 * \param kwds key->value dictonary.
 * \return True if everything goes well, false with a Python error setted otherwise.
 */
PYSIDE_API bool fillQtProperties(PyObject* qObj, const QMetaObject* metaObj, PyObject* kwds, const char** blackList, unsigned int blackListSize);

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

PYSIDE_API void initDynamicMetaObject(SbkObjectType* type, const QMetaObject* base);
PYSIDE_API void initQObjectSubType(SbkObjectType* type, PyObject* args, PyObject* kwds);

typedef void (*CleanupFunction)(void);

/**
 * Register a function to be called before python die
 */
PYSIDE_API void registerCleanupFunction(CleanupFunction func);
PYSIDE_API void runCleanupFunctions();

/**
 * Destroy a QCoreApplication taking care of destroy all instances of QObject first.
 */
PYSIDE_API void destroyQCoreApplication();

/**
 * Check for properties and signals registered on MetaObject and return these
 * \param cppSelf Is the QObject which contains the metaobject
 * \param self Python object of cppSelf
 * \param name Name of the argument which the function will try retrieve from MetaData
 * \return The Python object which contains the Data obtained in metaObject or the Python attribute related with name
 */
PYSIDE_API PyObject* getMetaDataFromQObject(QObject* cppSelf, PyObject* self, PyObject* name);

} //namespace PySide


#endif // PYSIDE_H


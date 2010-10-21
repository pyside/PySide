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

#ifndef PYSIDE_PROPERTY_H
#define PYSIDE_PROPERTY_H

#include <pysidemacros.h>
#include <Python.h>
#include <QObject>

extern "C"
{
    extern PYSIDE_API PyTypeObject PySideQPropertyType;

    struct PySideQPropertyPrivate;
    struct PYSIDE_API PySideQProperty
    {
        PyObject_HEAD
        PySideQPropertyPrivate* d;
    };

    struct PySideSignalInstanceData;
};

namespace PySide
{

PYSIDE_API bool isQPropertyType(PyObject* pyObj);

/**
 * This function call set property function and pass value as arg
 * This function does not check the property object type
 *
 * @param   self The property object
 * @param   source The QObject witch has the property
 * @param   value The value to set in property
 * @return  Return 0 if ok or -1 if this function fail
 **/
PYSIDE_API int qpropertySet(PySideQProperty* self, PyObject* source, PyObject* value);

/**
 * This function call get property function
 * This function does not check the property object type
 *
 * @param   self The property object
 * @param   source The QObject witch has the property
 * @return  Return the result of property get function or 0 if this fail
 **/
PYSIDE_API PyObject* qpropertyGet(PySideQProperty* self, PyObject* source);

/**
 * This function return the notify name used on this property
 *
 * @param   self The property object
 * @return  Return a const char with the notify name used
 **/
PYSIDE_API const char* qpropertyGetNotify(PySideQProperty* self);


/**
 * This function search in the source object for desired property
 *
 * @param   source The QObject object
 * @param   name The property name
 * @return  Return a new reference to property object
 **/
PYSIDE_API PySideQProperty* qpropertyGetObject(PyObject* source, PyObject* name);

} //namespace PySide

#endif

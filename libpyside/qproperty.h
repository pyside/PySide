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

#ifndef PYSIDE_PROPERTY_H
#define PYSIDE_PROPERTY_H

#include <pysidemacros.h>
#include <Python.h>
#include <QObject>

namespace PySide
{

extern "C"
{
    PyAPI_DATA(PyTypeObject) QProperty_Type;
}; //extern "C"

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
PYSIDE_API int qproperty_set(PyObject* self, PyObject* source, PyObject* value);

/**
 * This function call get property function
 * This function does not check the property object type
 *
 * @param   self The property object
 * @param   source The QObject witch has the property
 * @return  Return the result of property get function or 0 if this fail
 **/
PYSIDE_API PyObject* qproperty_get(PyObject* self, PyObject* source);

/**
 * This function call reset property function
 * This function does not check the property object type
 *
 * @param   self The property object
 * @param   source The QObject witch has the property
 * @return  Return 0 if ok or -1 if this function fail
 **/
PYSIDE_API int qproperty_reset(PyObject* self, PyObject* source);


/**
 * This function return the property type
 * This function does not check the property object type
 *
 * @param   self The property object
 * @return  Return the property type name
 **/
PYSIDE_API const char* qproperty_get_type(PyObject* self);

/**
 * This function search in the source object for desired property
 *
 * @param   source The QObject object
 * @param   name The property name
 * @return  Return a new reference to property object
 **/
PYSIDE_API PyObject* qproperty_get_object(PyObject* source, PyObject* name);


/**
 * This function check if property has read function
 * This function does not check the property object type
 *
 * @param   self The property object
 * @return  Return a boolean value
 **/
PYSIDE_API bool qproperty_is_readble(PyObject* self);

/**
 * This function check if property has write function
 * This function does not check the property object type
 *
 * @param   self The property object
 * @return  Return a boolean value
 **/
PYSIDE_API bool qproperty_is_writable(PyObject* self);

/**
 * This function check if property has reset function
 * This function does not check the property object type
 *
 * @param   self The property object
 * @return  Return a boolean value
 **/
PYSIDE_API bool qproperty_has_reset(PyObject* self);

/**
 * This function check if property has the flag DESIGNABLE setted
 * This function does not check the property object type
 *
 * @param   self The property object
 * @return  Return a boolean value
 **/
PYSIDE_API bool qproperty_is_designable(PyObject* self);

/**
 * This function check if property has the flag SCRIPTABLE setted
 * This function does not check the property object type
 *
 * @param   self The property object
 * @return  Return a boolean value
 **/
PYSIDE_API bool qproperty_is_scriptable(PyObject* self);

/**
 * This function check if property has the flag STORED setted
 * This function does not check the property object type
 *
 * @param   self The property object
 * @return  Return a boolean value
 **/
PYSIDE_API bool qproperty_is_stored(PyObject* self);

/**
 * This function check if property has the flag USER setted
 * This function does not check the property object type
 *
 * @param   self The property object
 * @return  Return a boolean value
 **/
PYSIDE_API bool qproperty_is_user(PyObject* self);

/**
 * This function check if property has the flag CONSTANT setted
 * This function does not check the property object type
 *
 * @param   self The property object
 * @return  Return a boolean value
 **/
PYSIDE_API bool qproperty_is_constant(PyObject* self);

/**
 * This function check if property has the flag FINAL setted
 * This function does not check the property object type
 *
 * @param   self The property object
 * @return  Return a boolean value
 **/
PYSIDE_API bool qproperty_is_final(PyObject* self);


} //namespace PySide

#endif

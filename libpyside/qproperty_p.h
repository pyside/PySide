/*
 * This file is part of the PySide project.
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

#ifndef PYSIDE_QPROPERTY_P_H
#define PYSIDE_QPROPERTY_P_H

#include <Python.h>

struct PySideQProperty;

namespace PySide
{

/**
 * Init PySide QProperty support system
 */
void initQProperty(PyObject* module);

/**
 * This function call reset property function
 * This function does not check the property object type
 *
 * @param   self The property object
 * @param   source The QObject witch has the property
 * @return  Return 0 if ok or -1 if this function fail
 **/
int qpropertyReset(PySideQProperty* self, PyObject* source);


/**
 * This function return the property type
 * This function does not check the property object type
 *
 * @param   self The property object
 * @return  Return the property type name
 **/
const char* qpropertyGetType(PySideQProperty* self);

/**
 * This function check if property has read function
 * This function does not check the property object type
 *
 * @param   self The property object
 * @return  Return a boolean value
 **/
bool qpropertyIsReadable(PySideQProperty* self);

/**
 * This function check if property has write function
 * This function does not check the property object type
 *
 * @param   self The property object
 * @return  Return a boolean value
 **/
bool qpropertyIsWritable(PySideQProperty* self);

/**
 * This function check if property has reset function
 * This function does not check the property object type
 *
 * @param   self The property object
 * @return  Return a boolean value
 **/
bool qpropertyHasReset(PySideQProperty* self);

/**
 * This function check if property has the flag DESIGNABLE setted
 * This function does not check the property object type
 *
 * @param   self The property object
 * @return  Return a boolean value
 **/
bool qpropertyIsDesignable(PySideQProperty* self);

/**
 * This function check if property has the flag SCRIPTABLE setted
 * This function does not check the property object type
 *
 * @param   self The property object
 * @return  Return a boolean value
 **/
bool qpropertyIsScriptable(PySideQProperty* self);

/**
 * This function check if property has the flag STORED setted
 * This function does not check the property object type
 *
 * @param   self The property object
 * @return  Return a boolean value
 **/
bool qpropertyIsStored(PySideQProperty* self);

/**
 * This function check if property has the flag USER setted
 * This function does not check the property object type
 *
 * @param   self The property object
 * @return  Return a boolean value
 **/
bool qpropertyIsUser(PySideQProperty* self);

/**
 * This function check if property has the flag CONSTANT setted
 * This function does not check the property object type
 *
 * @param   self The property object
 * @return  Return a boolean value
 **/
bool qpropertyIsConstant(PySideQProperty* self);

/**
 * This function check if property has the flag FINAL setted
 * This function does not check the property object type
 *
 * @param   self The property object
 * @return  Return a boolean value
 **/
bool qpropertyIsFinal(PySideQProperty* self);

} // namespace PySide

#endif

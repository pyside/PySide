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

#ifndef PYSIDEQMLREGISTERTYPE_H
#define PYSIDEQMLREGISTERTYPE_H

#include <Python.h>

struct SbkObjectType;

namespace PySide
{

extern void* nextQmlElementMemoryAddr;

/**
 * Init the QML support doign things like registering QtDeclarative.ListProperty and create the necessary stuff for
 * qmlRegisterType.
 *
 * \param module QtDeclarative python module
 */
void initQmlSupport(PyObject* module);

/**
 * PySide implementation of qmlRegisterType<T> function.
 *
 * \param pyObj Python type to be registered.
 * \param uri QML element uri.
 * \param versionMajor QML component major version.
 * \param versionMinor QML component minor version.
 * \param qmlName QML element name
 * \return the metatype id of the registered type.
 */
int qmlRegisterType(PyObject* pyObj, const char* uri, int versionMajor, int versionMinor, const char* qmlName);

}

#endif

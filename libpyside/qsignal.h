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

#ifndef PYSIDE_SIGNAL_H
#define PYSIDE_SIGNAL_H

#include <pysidemacros.h>
#include <Python.h>
#include <QObject>

namespace Shiboken
{
    struct SbkBaseWrapperType;
}

extern "C"
{
    extern PYSIDE_API PyTypeObject PySideSignalInstanceType;

    struct PySideSignalInstanceData
    {
        PyObject_HEAD
        char* signalName;
        char* signature;
        PyObject* source;
        PyObject* homonymousMethod;
        PyObject* next;
    };
}; //extern "C"

namespace PySide
{

PYSIDE_API PyObject* signalNew(const char* name, ...);
PYSIDE_API void signalUpdateSource(PyObject* source);
PYSIDE_API void addSignalToWrapper(Shiboken::SbkBaseWrapperType* wrapperType, const char* signalName, PyObject* signal);

} //namespace PySide

#endif

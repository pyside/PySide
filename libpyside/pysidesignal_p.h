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

#ifndef PYSIDE_QSIGNAL_P_H
#define PYSIDE_QSIGNAL_P_H

#include <sbkpython.h>

extern "C"
{
    extern PyTypeObject PySideSignalType;

    struct PySideSignal {
        PyObject_HEAD
        bool initialized;
        char* signalName;
        char** signatures;
        int signaturesSize;
        PyObject* homonymousMethod;
    };

    struct PySideSignalInstance;
    struct PySideSignalInstancePrivate {
        char* signalName;
        char* signature;
        PyObject* source;
        PyObject* homonymousMethod;
        PySideSignalInstance* next;
    };


}; //extern "C"

namespace PySide { namespace Signal {

    void            init(PyObject* module);
    bool            connect(PyObject* source, const char* signal, PyObject* callback);
    char*           getTypeName(PyObject*);
    const char**    getSignatures(PyObject* self, int *size);
    QString         codeCallbackName(PyObject* callback, const QString& funcName);

}} //namespace PySide

#endif

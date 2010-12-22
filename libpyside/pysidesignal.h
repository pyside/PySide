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

#include <QObject>
#include <QString>
#include <QStringList>

#include <pysidemacros.h>
#include <Python.h>
#include <basewrapper.h>

extern "C"
{
    extern PYSIDE_API PyTypeObject PySideSignalType;
    extern PYSIDE_API PyTypeObject PySideSignalInstanceType;

    //Internal object
    struct PYSIDE_API PySideSignal;

    struct PySideSignalInstancePrivate;
    struct PYSIDE_API PySideSignalInstance
    {
        PyObject_HEAD
        PySideSignalInstancePrivate* d;
    };
}; //extern "C"

namespace PySide { namespace Signal {

/**
 * This function creates a Signal object which stay attached to QObject class
 *
 * @param   name of the Signal to be registered on meta object
 * @param   signatures a list of signatures supported by this signal, ended with a NULL pointer
 * @return  Return a new reference to PyObject* of type  PySideSignal
 **/
PYSIDE_API PySideSignal* newObject(const char* name, ...);

/**
 * This function creates a Signal object which stay attached to QObject class based on a list of QMetaMethod
 *
 * @param   source of the Signal to be registered on meta object
 * @param   methods a list of QMetaMethod wich contains the supported signature
 * @return  Return a new reference to PyObject* of type  PySideSignal
 **/
PYSIDE_API PySideSignalInstance* newObjectFromMethod(PyObject* source, const QList<QMetaMethod>& methods);

/**
 * This function initializes the Signal object creating a PySideSignalInstance
 *
 * @param   self a Signal object used as base to PySideSignalInstance
 * @param   name the name to be used on PySideSignalInstance
 * @param   object the PyObject where the signal will be attached
 * @return  Return a new reference to PySideSignalInstance
 **/
PYSIDE_API PySideSignalInstance* initialize(PySideSignal* signal, PyObject* name, PyObject *object);

/**
 * This function is used to retrieve the object in which the sigal is attached
 *
 * @param   self The Signal object
 * @return  Return the internal reference to parent object of the signal
 **/
PYSIDE_API PyObject* getObject(PySideSignalInstance* signal);

/**
 * This function is used to retrieve the signal signature
 *
 * @param   self The Signal object
 * @return  Return the signal signature
 **/
PYSIDE_API const char* getSignature(PySideSignalInstance* signal);

/**
 * This function is used to retrieve the signal signature
 *
 * @param   self The Signal object
 * @return  Return the signal signature
 **/
PYSIDE_API void updateSourceObject(PyObject* source);

/**
 * This function is used to retrieve the signal signature
 *
 * @param   self The Signal object
 * @return  Return the signal signature
 **/
PYSIDE_API void addSignalToWrapper(SbkObjectType* wrapperType, const char* signalName, PySideSignal* signal);

/**
 * This function verify if the signature is a QtSignal base on SIGNAL flag
 * @param   signature   The signal signature
 * @return  Return true if this is a Qt Signal of false if not
 **/
PYSIDE_API bool isQtSignal(const char* signature);

/**
 * This function is similar as isQtSignal but this reaise a Python error if this faisl
 * @param   signature   The signal signature
 * @return  Return true if this is a Qt Signal of false if not
 **/
PYSIDE_API bool checkQtSignal(const char* signature);

/**
 * This function is used to retrieve the signature base on Signal and receiver callback
 * @param   signature   The signal signature
 * @param   receiver    The QObject which will receiver the signal
 * @param   callback    Callback function which will connect with signal
 * @param   encodeName  Used to specify if the returned signature will be encoded with Qt signal/slot style
 * @return  Return the callback signature
 **/
PYSIDE_API QString getCallbackSignature(const char* signal, QObject* receiver, PyObject* callback, bool encodeName);

/**
 * Function to parese the signature and return a list of argument types
 * @param   signature       The signal signature
 * @param   isShortCircuit  If this is a shortCircuit(python<->python) signal
 * @return  Return true if this is a Qt Signal of false if not
 * @todo    replace return type to QList<QByteArray>
 **/
QStringList getArgsFromSignature(const char* signature, bool* isShortCircuit = 0);

} //namespace Signal
} //namespace PySide

#endif

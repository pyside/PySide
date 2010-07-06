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

#ifndef SIGNALMANAGER_H
#define SIGNALMANAGER_H

#include "pysidemacros.h"
#include <Python.h>
#include <Qt>
#include <QStringList>
#include <QMetaMethod>

class QObject;

namespace PySide
{

/// Thin wrapper for PyObject which increases the reference count at the constructor but *NOT* at destructor.
class PYSIDE_API PyObjectWrapper
{
public:
    PyObjectWrapper();
    PyObjectWrapper(PyObject* me);
    PyObjectWrapper(const PyObjectWrapper &other);
    ~PyObjectWrapper();
    operator PyObject*() const;
private:
    PyObject* m_me;
};

PYSIDE_API bool isSignal(const char* signal);
PYSIDE_API bool checkSignal(const char* signal);
PYSIDE_API QString getCallbackSignature(const char* signal, QObject* receiver, PyObject* callback, bool encodeName);
QStringList getArgsFromSignature(const char* signature, bool* isShortCircuit = 0);

class PYSIDE_API SignalManager
{
public:
    static SignalManager& instance();
    QObject* globalReceiver();
    bool emitSignal(QObject* source, const char* signal, PyObject* args);

    static int qt_metacall(QObject* object, QMetaObject::Call call, int id, void** args);
    void addGlobalSlot(const char* slot, PyObject* callback);

    void globalReceiverConnectNotify(QObject *sender, int slotIndex);
    void globalReceiverDisconnectNotify(QObject *sender, int slotIndex);

    // Used to register a new signal/slot on QMetaobject of source.
    static bool registerMetaMethod(QObject* source, const char* signature, QMetaMethod::MethodType type);

    // Used to discovery if SignalManager was connected with object "destroyed()" signal.
    bool hasConnectionWith(const QObject *object);

    // Disconnect all signals managed by Globalreceiver
    void clear();
private:
    struct SignalManagerPrivate;
    SignalManagerPrivate* m_d;
    SignalManager();
    ~SignalManager();

    // disable copy
    SignalManager(const SignalManager&);
    SignalManager operator=(const SignalManager&);

    static int call_method(QObject* object, int id, void** args);
};

}

Q_DECLARE_METATYPE(PySide::PyObjectWrapper)

#endif

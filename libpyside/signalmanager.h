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
    PyObjectWrapper& operator=(const PyObjectWrapper &other);
private:
    PyObject* m_me;
    void*     m_data; //future
};

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
};

}

Q_DECLARE_METATYPE(PySide::PyObjectWrapper)

#endif

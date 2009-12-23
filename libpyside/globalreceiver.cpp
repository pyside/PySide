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

#include "globalreceiver.h"
#include <QMetaMethod>
#include <QDebug>
#include "signalmanager.h"
#include <autodecref.h>
#include "typeresolver.h"

using namespace PySide;

GlobalReceiver::GlobalReceiver() : m_metaObject(&QObject::staticMetaObject)
{
}

GlobalReceiver::~GlobalReceiver()
{
    foreach(PyObject* obj, m_slotReceivers)
        Py_DECREF(obj);
}

const QMetaObject* GlobalReceiver::metaObject() const
{
    return &m_metaObject;
}

void GlobalReceiver::addSlot(const char* slot, PyObject* callback)
{
    m_metaObject.addSlot(slot);
    int slotId = m_metaObject.indexOfSlot(slot);
    Py_INCREF(callback);
    m_slotReceivers[slotId] = callback;

    Q_ASSERT(slotId >= QObject::staticMetaObject.methodCount());
}

void GlobalReceiver::removeSlot(int slotId)
{
    PyObject* obj = m_slotReceivers.take(slotId);
    Py_XDECREF(obj);
}

int GlobalReceiver::qt_metacall(QMetaObject::Call call, int id, void** args)
{
    Q_ASSERT(call == QMetaObject::InvokeMetaMethod);
    Q_ASSERT(id >= QObject::staticMetaObject.methodCount());
    QMetaMethod slot = m_metaObject.method(id);
    Q_ASSERT(slot.methodType() == QMetaMethod::Slot);
    QList<QByteArray> paramTypes = slot.parameterTypes();

    PyObject* callback = m_slotReceivers.value(id);
    if (!callback) {
        qWarning("Unknown global slot.");
        return -1;
    }

    Shiboken::AutoDecRef preparedArgs(PyTuple_New(paramTypes.count()));
    for (int i = 0, max = paramTypes.count(); i < max; ++i) {
        PyObject* arg = TypeResolver::get(paramTypes[i].constData())->toPython(args[i+1]);
        PyTuple_SET_ITEM(preparedArgs.object(), i, arg);
    }

    Shiboken::AutoDecRef retval(PyObject_CallObject(callback, preparedArgs));
    if (!retval)
        qWarning("Error calling slot");
    return -1;
}

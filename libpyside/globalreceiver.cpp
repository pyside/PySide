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
#include <gilstate.h>
#include "typeresolver.h"


namespace PySide
{

class DynamicSlotData
{
    public:
        DynamicSlotData(PyObject *callback);
        void incRef();
        void decRef();
        int refCount() const;
        PyObject *callback() const;
        ~DynamicSlotData();

    private:
        int m_refCount;
        PyObject *m_callback;
};

}

using namespace PySide;

DynamicSlotData::DynamicSlotData(PyObject *callback)
    : m_refCount(0)
{
    m_callback = callback;
    Py_INCREF(callback);
}

void DynamicSlotData::incRef()
{
    m_refCount++;
}

void DynamicSlotData::decRef()
{
    m_refCount--;
}

int DynamicSlotData::refCount() const
{
    return m_refCount;
}

PyObject *DynamicSlotData::callback() const
{
    return m_callback;
}

DynamicSlotData::~DynamicSlotData()
{
    Py_XDECREF(m_callback);
}


GlobalReceiver::GlobalReceiver()
    : m_metaObject("GlobalReceiver", &QObject::staticMetaObject)
{
}

GlobalReceiver::~GlobalReceiver()
{
    foreach(DynamicSlotData* data, m_slotReceivers)
        delete data;
}

void GlobalReceiver::connectNotify(int slotId)
{
    if (m_slotReceivers.contains(slotId))
        m_slotReceivers[slotId]->incRef();
}

void GlobalReceiver::disconnectNotify(int slotId)
{
    if (m_slotReceivers.contains(slotId)) {
        DynamicSlotData *data = m_slotReceivers[slotId];
        data->decRef();
        if (data->refCount() == 0)
            removeSlot(slotId);
    }
}

const QMetaObject* GlobalReceiver::metaObject() const
{
    return &m_metaObject;
}

void GlobalReceiver::addSlot(const char* slot, PyObject* callback)
{
    m_metaObject.addSlot(slot);
    int slotId = m_metaObject.indexOfSlot(slot);
    if (!m_slotReceivers.contains(slotId)) {
        m_slotReceivers[slotId] = new DynamicSlotData(callback);
    }

    bool isShortCircuit = true;
    for (int i = 0; slot[i]; ++i) {
        if (slot[i] == '(') {
            isShortCircuit = false;
            break;
        }
    }
    if (isShortCircuit)
        m_shortCircuitSlots << slotId;

    Q_ASSERT(slotId >= QObject::staticMetaObject.methodCount());
}

void GlobalReceiver::removeSlot(int slotId)
{
    delete m_slotReceivers.take(slotId);
    m_metaObject.removeSlot(slotId);
    m_shortCircuitSlots.remove(slotId);
}

int GlobalReceiver::qt_metacall(QMetaObject::Call call, int id, void** args)
{
    Q_ASSERT(call == QMetaObject::InvokeMetaMethod);
    Q_ASSERT(id >= QObject::staticMetaObject.methodCount());
    QMetaMethod slot = m_metaObject.method(id);
    Q_ASSERT(slot.methodType() == QMetaMethod::Slot);

    DynamicSlotData* data = m_slotReceivers.value(id);
    if (!data) {
        qWarning() << "Unknown global slot, id:" << id;
        return -1;
    }

    Shiboken::GilState gil;
    int numArgs;
    PyObject* retval = 0;
    PyObject* callback = data->callback();
    if (m_shortCircuitSlots.contains(id)) {
        retval = PyObject_CallObject(callback, reinterpret_cast<PyObject*>(args[1]));
    } else {
        QList<QByteArray> paramTypes = slot.parameterTypes();
        numArgs = paramTypes.count();
        Shiboken::AutoDecRef preparedArgs(PyTuple_New(paramTypes.count()));
        for (int i = 0, max = paramTypes.count(); i < max; ++i) {
            PyObject* arg = Shiboken::TypeResolver::get(paramTypes[i].constData())->toPython(args[i+1]);
            PyTuple_SET_ITEM(preparedArgs.object(), i, arg);
        }

        retval = PyObject_CallObject(callback, preparedArgs);
    }

    if (!retval)
        qWarning() << "Error calling slot" << m_metaObject.method(id).signature();
    else
        Py_DECREF(retval);
    return -1;
}

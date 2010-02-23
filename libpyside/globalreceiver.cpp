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
#include <QEvent>
#include <autodecref.h>
#include <gilstate.h>

#include "typeresolver.h"
#include "signalmanager.h"

#define RECEIVER_DESTROYED_SLOT_NAME "__receiverDestroyed__(QObject*)"

namespace PySide
{
class DynamicSlotData
{
    public:
        DynamicSlotData(int id, PyObject* callback);
        void addRef(const QObject* o);
        void decRef(const QObject* o);
        void clear();
        bool hasRefTo(const QObject* o) const;
        int refCount() const;
        int id() const;
        PyObject* callback() const;
        ~DynamicSlotData();

    private:
        int m_id;
        PyObject* m_callback;
        QSet<const QObject*> m_refs;
};

}

using namespace PySide;

DynamicSlotData::DynamicSlotData(int id, PyObject* callback)
    : m_id(id)
{
    m_callback = callback;
    Py_INCREF(callback);
}

void DynamicSlotData::addRef(const QObject *o)
{
    m_refs.insert(o);
}

void DynamicSlotData::decRef(const QObject *o)
{
    m_refs.remove(o);
}

int DynamicSlotData::refCount() const
{
    return m_refs.size();
}


PyObject* DynamicSlotData::callback() const
{
    return m_callback;
}

int DynamicSlotData::id() const
{
    return m_id;
}

bool DynamicSlotData::hasRefTo(const QObject *o) const
{
    return m_refs.contains(o);
}

void DynamicSlotData::clear()
{
    m_refs.clear();
}

DynamicSlotData::~DynamicSlotData()
{
    Py_DECREF(m_callback);
}


GlobalReceiver::GlobalReceiver()
    : m_metaObject("GlobalReceiver", &QObject::staticMetaObject)
{
    //slot used to be notifyed of object destrouction
    m_metaObject.addSlot(RECEIVER_DESTROYED_SLOT_NAME);
}

GlobalReceiver::~GlobalReceiver()
{
    foreach(DynamicSlotData* data, m_slotReceivers) {
        data->clear();
        delete data;
    }
}

void GlobalReceiver::connectNotify(QObject* source, int slotId)
{
    if (m_slotReceivers.contains(slotId)) {
        m_slotReceivers[slotId]->addRef(source);
    }
}

void GlobalReceiver::disconnectNotify(QObject* source, int slotId)
{
    if (m_slotReceivers.contains(slotId)) {
        QObject::disconnect(source, SIGNAL(destroyed(QObject*)), this, "1"RECEIVER_DESTROYED_SLOT_NAME);

        DynamicSlotData *data = m_slotReceivers[slotId];
        data->decRef(source);
        if (data->refCount() == 0) {
            removeSlot(slotId);
        }
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
        m_slotReceivers[slotId] = new DynamicSlotData(slotId, callback);
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
    if (m_slotReceivers.contains(slotId)) {
        delete m_slotReceivers.take(slotId);
        m_metaObject.removeSlot(slotId);
        m_shortCircuitSlots.remove(slotId);
    }
}

bool GlobalReceiver::hasConnectionWith(const QObject *object)
{
    QHash<int, DynamicSlotData*>::iterator i = m_slotReceivers.begin();
    while(i != m_slotReceivers.end()) {
        if (i.value()->hasRefTo(object)) {
            return true;
        }
        i++;
    }
    return false;
}

int GlobalReceiver::qt_metacall(QMetaObject::Call call, int id, void** args)
{
    Q_ASSERT(call == QMetaObject::InvokeMetaMethod);
    Q_ASSERT(id >= QObject::staticMetaObject.methodCount());
    QMetaMethod slot = m_metaObject.method(id);
    Q_ASSERT(slot.methodType() == QMetaMethod::Slot);

    if (strcmp(slot.signature(), RECEIVER_DESTROYED_SLOT_NAME) == 0) {
        QObject *arg = *(QObject**)args[1];

        QHash<int, DynamicSlotData*>::iterator i = m_slotReceivers.begin();
        while(i != m_slotReceivers.end()) {
            if (i.value()->hasRefTo(arg)) {
                disconnectNotify(arg, i.key());
                break;
            }
            i++;
        }
        return -1;
    }

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

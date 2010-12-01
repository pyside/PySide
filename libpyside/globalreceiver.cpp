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

#include "globalreceiver.h"
#include "dynamicqmetaobject_p.h"

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
    : m_metaObject(GLOBAL_RECEIVER_CLASS_NAME, &QObject::staticMetaObject)
{
    //slot used to be notifyed of object destrouction
    m_metaObject.addSlot(RECEIVER_DESTROYED_SLOT_NAME);
}

GlobalReceiver::~GlobalReceiver()
{
    while(!m_slotReceivers.empty()) {
        DynamicSlotData* data = m_slotReceivers.take(m_slotReceivers.begin().key());
        data->clear();
        delete data;
    }
}

void GlobalReceiver::connectNotify(QObject* source, int slotId)
{
    if (m_slotReceivers.contains(slotId)) {
        DynamicSlotData* data = m_slotReceivers[slotId];
        if (!data->hasRefTo(source))
            QObject::connect(source, SIGNAL(destroyed(QObject*)), this, "1"RECEIVER_DESTROYED_SLOT_NAME);
        data->addRef(source);
    }
}

void GlobalReceiver::disconnectNotify(QObject* source, int slotId)
{
   if (m_slotReceivers.contains(slotId)) {
        DynamicSlotData *data = m_slotReceivers[slotId];
        data->decRef(source);
        if (data->refCount() == 0)
            removeSlot(slotId);

        if (!hasConnectionWith(source))
            QObject::disconnect(source, SIGNAL(destroyed(QObject*)), this, "1"RECEIVER_DESTROYED_SLOT_NAME);
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
    if (!m_slotReceivers.contains(slotId))
        m_slotReceivers[slotId] = new DynamicSlotData(slotId, callback);

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

        //avoid hash changes during the destruction
        QHash<int, DynamicSlotData*> copy = m_slotReceivers;
        QHash<int, DynamicSlotData*>::iterator i = copy.begin();
        while(i != copy.end()) {
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
        PyErr_Print();
    else
        Py_DECREF(retval);

    return -1;
}

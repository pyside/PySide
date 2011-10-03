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

#include "globalreceiverv2.h"
#include "dynamicqmetaobject_p.h"
#include "pysideweakref.h"

#include <QMetaMethod>
#include <QDebug>
#include <QEvent>
#include <QLinkedList>
#include <autodecref.h>
#include <gilstate.h>

#include "typeresolver.h"
#include "signalmanager.h"

#define RECEIVER_DESTROYED_SLOT_NAME "__receiverDestroyed__(QObject*)"

namespace
{
    static int DESTROY_SIGNAL_ID = 0;
    static int DESTROY_SLOT_ID = 0;
}

namespace PySide
{
class DynamicSlotDataV2
{
    public:
        DynamicSlotDataV2(PyObject* callback, GlobalReceiverV2* parent);
        ~DynamicSlotDataV2();

        int addSlot(const char* signature);
        int id(const char* signature) const;
        PyObject* callback();
        QByteArray hash() const;
        void notify();

        static void onCallbackDestroyed(void* data);
        static QByteArray hash(PyObject *callback);


    private:
        bool m_isMethod;
        PyObject* m_callback;
        PyObject* m_pythonSelf;
        PyObject* m_pyClass;
        PyObject* m_weakRef;
        QMap<QByteArray, int> m_signatures;
        GlobalReceiverV2* m_parent;
        QByteArray m_hash;
};

}

using namespace PySide;

DynamicSlotDataV2::DynamicSlotDataV2(PyObject* callback, GlobalReceiverV2* parent)
    : m_pythonSelf(0), m_pyClass(0), m_weakRef(0), m_parent(parent)
{
    m_isMethod = PyMethod_Check(callback);
    if (m_isMethod) {
        //Can not store calback pointe because this will be destroyed at the end of the scope
        //To avoid increment intance reference keep the callback information
        m_callback = PyMethod_GET_FUNCTION(callback);
#ifndef IS_PY3K
        m_pyClass = PyMethod_GET_CLASS(callback);
#endif
        m_pythonSelf = PyMethod_GET_SELF(callback);

        //monitor class from method lifetime
        m_weakRef = WeakRef::create(m_pythonSelf, DynamicSlotDataV2::onCallbackDestroyed, this);

        m_hash = QByteArray::number((qlonglong)PyObject_Hash(m_callback))
                 + QByteArray::number((qlonglong)PyObject_Hash(m_pythonSelf));

    } else {
        m_callback = callback;
        Py_INCREF(m_callback);

        m_hash = QByteArray::number((qlonglong)PyObject_Hash(m_callback));
    }
}

QByteArray DynamicSlotDataV2::hash() const
{
    return m_hash;
}

QByteArray DynamicSlotDataV2::hash(PyObject* callback)
{
    Shiboken::GilState gil;
    if (PyMethod_Check(callback))
        return  QByteArray::number((qlonglong)PyObject_Hash(PyMethod_GET_FUNCTION(callback))) 
              + QByteArray::number((qlonglong)PyObject_Hash(PyMethod_GET_SELF(callback)));
    else
        return QByteArray::number((qlonglong)PyObject_Hash(callback));
}

PyObject* DynamicSlotDataV2::callback()
{
    PyObject* callback = m_callback;

    //create a callback based on method data
    if (m_isMethod)
#ifdef IS_PY3K
        callback = PyMethod_New(m_callback, m_pythonSelf);
#else
        callback = PyMethod_New(m_callback, m_pythonSelf, m_pyClass);
#endif
    else
        Py_INCREF(callback);

    return callback;
}

int DynamicSlotDataV2::id(const char* signature) const
{
    if (m_signatures.contains(signature))
        return m_signatures[signature];
    return -1;
}

int DynamicSlotDataV2::addSlot(const char* signature)
{
    int index = id(signature);
    if (index == -1) {
        DynamicQMetaObject *dmo = const_cast<DynamicQMetaObject*>(reinterpret_cast<const DynamicQMetaObject*>(m_parent->metaObject()));
        index = m_signatures[signature] = dmo->addSlot(signature);
    }
    return index;
}

void DynamicSlotDataV2::onCallbackDestroyed(void *data)
{
    DynamicSlotDataV2* self = reinterpret_cast<DynamicSlotDataV2*>(data);
    self->m_weakRef = 0;
    delete self->m_parent;
}

DynamicSlotDataV2::~DynamicSlotDataV2()
{
    Shiboken::GilState gil;

    Py_XDECREF(m_weakRef);
    m_weakRef = 0;

    if (!m_isMethod)
       Py_DECREF(m_callback);
}

GlobalReceiverV2::GlobalReceiverV2(PyObject *callback, SharedMap map)
    : QObject(0), m_metaObject(GLOBAL_RECEIVER_CLASS_NAME, &QObject::staticMetaObject), m_sharedMap(map)
{
    m_data = new DynamicSlotDataV2(callback, this);
    m_metaObject.addSlot(RECEIVER_DESTROYED_SLOT_NAME);
    m_metaObject.update();
    m_refs.append(NULL);


    if (DESTROY_SIGNAL_ID == 0)
        DESTROY_SIGNAL_ID = QObject::staticMetaObject.indexOfSignal("destroyed(QObject*)");

    if (DESTROY_SLOT_ID == 0)
        DESTROY_SLOT_ID = m_metaObject.indexOfSlot(RECEIVER_DESTROYED_SLOT_NAME);


}

GlobalReceiverV2::~GlobalReceiverV2()
{
    m_refs.clear();
    //Remove itself from map
    m_sharedMap->remove(m_data->hash());
    delete m_data;
}

int GlobalReceiverV2::addSlot(const char* signature)
{
    return m_data->addSlot(signature);
}

void GlobalReceiverV2::incRef(const QObject* link)
{
    if (link) {
        if (!m_refs.contains(link)) {
            if (QMetaObject::connect(link, DESTROY_SIGNAL_ID, this, DESTROY_SLOT_ID))
                m_refs.append(link);
            else
                Q_ASSERT(false);
        } else {
            m_refs.append(link);
        }
    } else {
        m_refs.append(NULL);
    }
}

void GlobalReceiverV2::decRef(const QObject* link)
{
    if (m_refs.size() <= 0)
        return;


    m_refs.removeOne(link);
    if (link) {
        if (!m_refs.contains(link)) {
            bool result = QMetaObject::disconnect(link, DESTROY_SIGNAL_ID, this, DESTROY_SLOT_ID);
            Q_ASSERT(result);
            if (!result)
                return;
        }
    }

    if (m_refs.size() == 0)
        delete this;

}

int GlobalReceiverV2::refCount(const QObject* link) const
{
    if (link)
        return m_refs.count(link);

    return m_refs.size();
}

void GlobalReceiverV2::notify()
{
    QSet<const QObject*> objs = QSet<const QObject*>::fromList(m_refs);
    foreach(const QObject* o, objs) {
        QMetaObject::disconnect(o, DESTROY_SIGNAL_ID, this, DESTROY_SLOT_ID);
        QMetaObject::connect(o, DESTROY_SIGNAL_ID, this, DESTROY_SLOT_ID);
    }
}

QByteArray GlobalReceiverV2::hash() const
{
    return m_data->hash();
}

QByteArray GlobalReceiverV2::hash(PyObject* callback)
{
    return DynamicSlotDataV2::hash(callback);
}

const QMetaObject* GlobalReceiverV2::metaObject() const
{
    return m_metaObject.update();
}

int GlobalReceiverV2::qt_metacall(QMetaObject::Call call, int id, void** args)
{
    Q_ASSERT(call == QMetaObject::InvokeMetaMethod);
    Q_ASSERT(id >= QObject::staticMetaObject.methodCount());

    QMetaMethod slot = metaObject()->method(id);
    Q_ASSERT(slot.methodType() == QMetaMethod::Slot);

    if (id == DESTROY_SLOT_ID) {
        if (m_refs.size() == 0)
            return -1;
        QObject *obj = *(QObject**)args[1];
        incRef(); //keep the object live (safe ref)
        m_refs.removeAll(obj); // remove all refs to this object
        decRef(); //remove the safe ref
    } else {
        bool isShortCuit = (strstr(slot.signature(), "(") == 0);
        Shiboken::AutoDecRef callback(m_data->callback());
        SignalManager::callPythonMetaMethod(slot, args, callback, isShortCuit);
    }

    return -1;
}

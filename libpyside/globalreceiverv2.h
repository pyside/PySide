/*
* This file is part of the PySide project.
*
* Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
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

#ifndef GLOBALRECEIVER_V2_H
#define GLOBALRECEIVER_V2_H

#include <sbkpython.h>
#include <QObject>
#include <QHash>
#include <QSet>
#include <QSharedPointer>
#include <QLinkedList>
#include <QByteArray>

#include "dynamicqmetaobject.h"

namespace PySide
{

class DynamicSlotDataV2;
class GlobalReceiverV2;

typedef QSharedPointer< QMap<QByteArray, GlobalReceiverV2*> >  SharedMap;

/**
 * A class used to make the link between the C++ Signal/Slot and Python callback
 * This class is used internally by SignalManager
 **/

class GlobalReceiverV2 : public QObject
{
public:
    /**
     * Create a GlobalReceiver object that will call 'callback' argumentent
     *
     * @param   callback    A Python callable object (can be a method or not)
     * @param   ma          A SharedPointer used on Signal manager that contains all instaces of GlobalReceiver
     **/
    GlobalReceiverV2(PyObject *callback, SharedMap map);

    /**
     * Destructor
     **/
    ~GlobalReceiverV2();

    /**
     * Reimplemented function from QObject
     **/
    int qt_metacall(QMetaObject::Call call, int id, void** args);
    const QMetaObject* metaObject() const;

    /**
     * Add a extra slot to this object
     *
     * @param   signature   The signature of the slot to be added
     * @return  The index of this slot on metaobject
     **/
    int addSlot(const char* signature);

    /**
     * Notify to GlobalReceiver about when a new connection was made
     **/
    void notify();

    /**
     * Used to increment the reference of the GlobalReceiver object
     *
     * @param   link    This is a optional paramenter used to link the ref to some QObject life
     **/
    void incRef(const QObject* link = 0);

    /**
     * Used to decrement the reference of the GlobalReceiver object
     *
     * @param   link    This is a optional paramenter used to dismiss the link ref to some QObject
     **/
    void decRef(const QObject* link = 0);

    /*
     * Return the count of refs which the GlobalReceiver has
     *
     * @param   link    If any QObject was passed, the function return the number of references relative to this 'link' object
     * @return  The number of references
     **/
    int refCount(const QObject* link) const;

    /**
     * Use to retrive the unique hash of this GlobalReceiver object
     *
     * @return  a string with a unique id based on GlobalReceiver contents
     **/
    QByteArray hash() const;

    /**
     * Use to retrive the unique hash of the PyObject based on GlobalReceiver rules
     *
     * @param   callback The Python callable object used to calculate the id
     * @return  a string with a unique id based on GlobalReceiver contents
     **/
    static QByteArray hash(PyObject* callback);

private:
    DynamicQMetaObject m_metaObject;
    DynamicSlotDataV2 *m_data;
    QList<const QObject*> m_refs;
    int m_ref;
    SharedMap m_sharedMap;
};

}

#endif

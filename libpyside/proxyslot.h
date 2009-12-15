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

#include <QObject>
#include <QHash>

namespace PySide
{

class AbstractQObjectConnection;

class ProxySlot : public QObject
{
public:
    ProxySlot(QObject* signalSource);
    bool connect(AbstractQObjectConnection* connection);
protected:
    /**
    *   Qt's meta-object system uses the qt_metacall() function to access the
    *   meta-information for a particular QObject object (its signals, slots,
    *   properties, etc.).
    *
    *   About the implemmentation
    *
    *   The call may indicate access to the meta-object of the QObject base
    *   class, we need to take care of this use case.
    *   If the QObject::qt_metacall() call returns -1, this means that the
    *   metacall has been handled by QObject and that there is nothing to do.
    *   In that case, we return immediately. Similarly, if the metacall isn't
    *   a slot invocation, we follow QObject's convention and return an
    *   identifier that can be handled by a subclass.
    *
    *   If all goes well, we invoke the specified slot and return -1 to
    *   indicate that the metacall has been processed.
    *
    *   \see \link http://doc.trolltech.com/qq/qq16-dynamicqobject.html
    */
    int qt_metacall(QMetaObject::Call call, int id, void **args);

private:
    QObject* m_signalSource;
    int m_nextSlotIndex;
    // slot_index => connection_info, used by qt_metacall
    // to recover the connection_info
    QHash<int, AbstractQObjectConnection*> m_connections;

    void attachAbstractConnection(AbstractQObjectConnection* connection);
};

}
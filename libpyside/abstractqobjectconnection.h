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

#ifndef ABSTRACTQOBJECTCONNECTION_H
#define ABSTRACTQOBJECTCONNECTION_H
#include <Python.h>
#include <Qt>
#include <QStringList>

class QObject;

namespace PySide
{
class AbstractQObjectConnection
{
public:
    AbstractQObjectConnection(QObject* source, const char* signal, Qt::ConnectionType connectionType);
    virtual ~AbstractQObjectConnection() {}

    QObject* source() const
    {
        return m_source;
    }
    void setSignalIndex(int signalIndex)
    {
        m_signalIndex = signalIndex;
    }

    int signalIndex() const
    {
        return m_signalIndex;
    }

    void setSlotIndex(int slotIndex)
    {
        m_slotIndex = slotIndex;
    }

    int slotIndex() const
    {
        return m_slotIndex;
    }

    Qt::ConnectionType type() const
    {
        return m_connectionType;
    }

    void trigger(void** args);
    virtual void trigger(PyObject* args) = 0;
private:
    QObject* m_source;
    QStringList m_signalArgs;
    Qt::ConnectionType m_connectionType;
    int m_signalIndex;
    int m_slotIndex;
};
}

#endif

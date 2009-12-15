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

#include "signalslotconnection.h"
#include <QDebug>

using namespace PySide;

SignalSlotConnection::SignalSlotConnection(QObject* source, const char* signal, PyObject* callback, Qt::ConnectionType connectionType)
 : AbstractQObjectConnection(source, signal, connectionType), m_receiver(0)
{
    if (PyMethod_Check(callback)) {
        m_function = PyMethod_GET_FUNCTION(callback);
        if (PyObject* self = PyMethod_GET_SELF(callback))
            m_receiver = self;
    } else {
        m_function = callback;
    }
    Py_INCREF(m_function);
    PyCodeObject* objCode = reinterpret_cast<PyCodeObject*>(PyFunction_GET_CODE(m_function));
    m_numSlotArgs = objCode->co_flags & CO_VARARGS ? -1 : objCode->co_argcount;
}

SignalSlotConnection::~SignalSlotConnection()
{
    Py_DECREF(m_function);
}

void SignalSlotConnection::trigger(PyObject* args)
{
    int useSelf = m_receiver ? 1 : 0;
    int numArgs = PySequence_Size(args);
    PyObject* preparedArgs = PyTuple_New(numArgs + useSelf);
    if (m_receiver)
        PyTuple_SetItem(preparedArgs, 0, m_receiver);
    for (int i = 0; i < numArgs; ++i)
        PyTuple_SET_ITEM(preparedArgs, i + useSelf, PyTuple_GET_ITEM(args, i));

    qDebug() << "num args: " << m_numSlotArgs;
    // sliceamento
//     if (m_num_slot_args != -1 && m_num_slot_args < python::len(args)) {
//         args = python::list(args.slice(0, m_num_slot_args));
//     }
    qDebug() << "Receiver" << m_receiver;
    qDebug() << "numargs" << numArgs;
    PyObject* retval = PyObject_CallObject(m_function, preparedArgs);
    if (retval) {
        Py_DECREF(retval);
    } else {
        qWarning(qPrintable(QString("Error calling slot ")+
                 PyString_AS_STRING(reinterpret_cast<PyCodeObject*>(PyFunction_GET_CODE(m_function))->co_name)));
    }
}

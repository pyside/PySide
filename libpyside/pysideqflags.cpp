/*
* This file is part of the PySide project.
*
* Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
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

#include "pysideqflags.h"
#include <sbkenum.h>

extern "C" {
    struct SbkConverter;

    /**
     * Type of all QFlags
     */
    struct PySideQFlagsType
    {
        PyHeapTypeObject super;
        SbkConverter* converter;
    };

    #define PYSIDE_QFLAGS(X) reinterpret_cast<PySideQFlagsObject*>(X)

    PyObject* PySideQFlagsNew(PyTypeObject *type, PyObject *args, PyObject *kwds)
    {
        PySideQFlagsObject* self = PyObject_New(PySideQFlagsObject, type);
        self->ob_value = 0;
        return reinterpret_cast<PyObject*>(self);
    }

    static long getNumberValue(PyObject* v)
    {
        PyObject* number = PyNumber_Long(v);
        long result = PyLong_AsLong(number);
        Py_XDECREF(number);
        return result;
    }

    PyObject* PySideQFlagsRichCompare(PyObject *self, PyObject *other, int op)
    {
        int result = 0;
        if (!PyNumber_Check(other)) {
            PyErr_BadArgument();
            return NULL;
        }

        long valA = PYSIDE_QFLAGS(self)->ob_value;
        long valB = getNumberValue(other);

        if (self == other) {
            result = 1;
        } else  {
            switch (op) {
            case Py_EQ:
                result = (valA == valB);
                break;
            case Py_NE:
                result = (valA != valB);
                break;
            case Py_LE:
                result = (valA <= valB);
                break;
            case Py_GE:
                result = (valA >= valB);
                break;
            case Py_LT:
                result = (valA < valB);
                break;
            case Py_GT:
                result = (valA > valB);
                break;
            default:
                PyErr_BadArgument();
                return NULL;
            }
        }
        if (result)
            Py_RETURN_TRUE;
        else
            Py_RETURN_FALSE;
    }
}

namespace PySide
{
namespace QFlags
{
    PyTypeObject* create(const char* name, PyNumberMethods* numberMethods)
    {
        PyTypeObject* type = reinterpret_cast<PyTypeObject*>(new PySideQFlagsType);
        ::memset(type, 0, sizeof(PySideQFlagsType));
        Py_TYPE(type) = &PyType_Type;
        type->tp_basicsize = sizeof(PySideQFlagsObject);
        type->tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_CHECKTYPES;
        type->tp_name = name;
        type->tp_new = &PySideQFlagsNew;
        type->tp_as_number = numberMethods;
        type->tp_richcompare = &PySideQFlagsRichCompare;

        if (PyType_Ready(type) < 0)
            return 0;

        return type;
    }

    PySideQFlagsObject* newObject(long value, PyTypeObject* type)
    {
        PySideQFlagsObject* qflags = PyObject_New(PySideQFlagsObject, type);
        qflags->ob_value = value;
        return qflags;
    }

    long getValue(PySideQFlagsObject* self)
    {
        return self->ob_value;
    }
}
}


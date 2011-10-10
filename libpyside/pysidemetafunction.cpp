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
#include <sbkpython.h>
#include "pysidemetafunction.h"

#include <shiboken.h>
#include <QObject>
#include <QMetaMethod>
#include <QDebug>

extern "C"
{

struct PySideMetaFunctionPrivate
{
    QObject* qobject;
    QMetaMethod method;
};

//methods
static void         functionFree(void*);
static PyObject*    functionCall(PyObject*, PyObject*, PyObject*);

PyTypeObject PySideMetaFunctionType = {
    PyVarObject_HEAD_INIT(0, 0)
    /*tp_name*/             "PySide.MetaFunction",
    /*tp_basicsize*/        sizeof(PySideMetaFunction),
    /*tp_itemsize*/         0,
    /*tp_dealloc*/          0,
    /*tp_print*/            0,
    /*tp_getattr*/          0,
    /*tp_setattr*/          0,
    /*tp_compare*/          0,
    /*tp_repr*/             0,
    /*tp_as_number*/        0,
    /*tp_as_sequence*/      0,
    /*tp_as_mapping*/       0,
    /*tp_hash*/             0,
    /*tp_call*/             functionCall,
    /*tp_str*/              0,
    /*tp_getattro*/         0,
    /*tp_setattro*/         0,
    /*tp_as_buffer*/        0,
    /*tp_flags*/            Py_TPFLAGS_DEFAULT,
    /*tp_doc*/              "MetaFunction",
    /*tp_traverse*/         0,
    /*tp_clear*/            0,
    /*tp_richcompare*/      0,
    /*tp_weaklistoffset*/   0,
    /*tp_iter*/             0,
    /*tp_iternext*/         0,
    /*tp_methods*/          0,
    /*tp_members*/          0,
    /*tp_getset*/           0,
    /*tp_base*/             0,
    /*tp_dict*/             0,
    /*tp_descr_get*/        0,
    /*tp_descr_set*/        0,
    /*tp_dictoffset*/       0,
    /*tp_init*/             0,
    /*tp_alloc*/            0,
    /*tp_new*/              PyType_GenericNew,
    /*tp_free*/             functionFree,
    /*tp_is_gc*/            0,
    /*tp_bases*/            0,
    /*tp_mro*/              0,
    /*tp_cache*/            0,
    /*tp_subclasses*/       0,
    /*tp_weaklist*/         0,
    /*tp_del*/              0,
};

void functionFree(void *self)
{
    PySideMetaFunction* function = reinterpret_cast<PySideMetaFunction*>(self);
    delete function->d;
}

PyObject* functionCall(PyObject* self, PyObject* args, PyObject* kw)
{
    static Shiboken::TypeResolver* typeResolver = Shiboken::TypeResolver::get("QVariant");
    Q_ASSERT(typeResolver);

    QGenericArgument gArgs[10];
    QVariant vArgs[10];
    PySideMetaFunction* function = reinterpret_cast<PySideMetaFunction*>(self);
    QMetaMethod method = function->d->method;
    int argsGiven = method.parameterTypes().size();

    for (int i = 0; i < argsGiven; ++i) {
        Shiboken::AutoDecRef pyArg(PySequence_GetItem(args, i));
        gArgs[i] = Q_ARG(QVariant, vArgs[i]);
        void* v[1] = { &vArgs[i] };
        typeResolver->toCpp(pyArg, v);
    }

    QVariant retVariant;
    QGenericReturnArgument returnValue = Q_RETURN_ARG(QVariant, retVariant);
    method.invoke(function->d->qobject, returnValue, gArgs[0], gArgs[1], gArgs[2], gArgs[3], gArgs[4], gArgs[5], gArgs[6], gArgs[7], gArgs[8], gArgs[9]);


    if (retVariant.isValid())
        return typeResolver->toPython(&retVariant);

    Py_RETURN_NONE;
}

} // extern "C"

namespace PySide { namespace MetaFunction {

void init(PyObject* module)
{
    if (PyType_Ready(&PySideMetaFunctionType) < 0)
        return;

    PyModule_AddObject(module, "MetaFunction", ((PyObject*)&PySideMetaFunctionType));
}

PySideMetaFunction* newObject(QObject* source, int methodIndex)
{
    if (methodIndex >= source->metaObject()->methodCount())
        return 0;

    QMetaMethod method = source->metaObject()->method(methodIndex);
    if ((method.methodType() == QMetaMethod::Slot) ||
        (method.methodType() == QMetaMethod::Method)) {
        PySideMetaFunction* function = PyObject_New(PySideMetaFunction, &PySideMetaFunctionType);
        function->d = new PySideMetaFunctionPrivate();
        function->d->qobject = source;
        function->d->method = method;
        return function;
    }
    return 0;
}

} //namespace MetaFunction
} //namespace PySide


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

#include <shiboken.h>
#include <Python.h>
#include <QDebug>

#include "qproperty.h"
#include "qproperty_p.h"
#include "dynamicqmetaobject_p.h"
#include "qsignal.h"
#include "qsignal_p.h"

#define QPROPERTY_CLASS_NAME "Property"

extern "C"
{

struct PySidePropertyPrivate {
    char* typeName;
    PyObject* type;
    PyObject* fget;
    PyObject* fset;
    PyObject* freset;
    PyObject* fdel;
    PyObject* notify;
    char* notifySignature;
    char* doc;
    bool designable;
    bool scriptable;
    bool stored;
    bool user;
    bool constant;
    bool final;
};

static int qpropertyTpInit(PyObject*, PyObject*, PyObject*);
static void qpropertyFree(void*);

PyTypeObject PySidePropertyType = {
    PyObject_HEAD_INIT(0)
    0,                         /*ob_size*/
    QPROPERTY_CLASS_NAME,      /*tp_name*/
    sizeof(PySideProperty),   /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    0,                         /*tp_dealloc*/
    0,                         /*tp_print*/
    0,                         /*tp_getattr*/
    0,                         /*tp_setattr*/
    0,                         /*tp_compare*/
    0,                         /*tp_repr*/
    0,                         /*tp_as_number*/
    0,                         /*tp_as_sequence*/
    0,                         /*tp_as_mapping*/
    0,                         /*tp_hash */
    0,                         /*tp_call*/
    0,                         /*tp_str*/
    0,                         /*tp_getattro*/
    0,                         /*tp_setattro*/
    0,                         /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT,        /*tp_flags*/
    0,                         /*tp_doc */
    0,                         /*tp_traverse */
    0,                         /*tp_clear */
    0,                         /*tp_richcompare */
    0,                         /*tp_weaklistoffset */
    0,                         /*tp_iter */
    0,                         /*tp_iternext */
    0,                         /*tp_methods */
    0,                         /*tp_members */
    0,                         /*tp_getset */
    0,                         /*tp_base */
    0,                         /*tp_dict */
    0,                         /*tp_descr_get */
    0,                         /*tp_descr_set */
    0,                         /*tp_dictoffset */
    qpropertyTpInit,           /*tp_init */
    0,                         /*tp_alloc */
    PyType_GenericNew,         /*tp_new */
    qpropertyFree,             /*tp_free */
    0,                         /*tp_is_gc */
    0,                         /*tp_bases */
    0,                         /*tp_mro */
    0,                         /*tp_cache */
    0,                         /*tp_subclasses */
    0,                         /*tp_weaklist */
    0,                         /*tp_del */
};

int qpropertyTpInit(PyObject* self, PyObject* args, PyObject* kwds)
{
    PyObject* type = 0;
    PySideProperty* data = reinterpret_cast<PySideProperty*>(self);
    PySidePropertyPrivate* pData = (PySidePropertyPrivate*) malloc(sizeof(PySidePropertyPrivate));
    data->d = pData;
    pData->fset = 0;
    pData->fget = 0;
    pData->freset = 0;
    pData->fdel = 0;
    pData->designable = true;
    pData->scriptable = true;
    pData->stored = true;
    pData->typeName = 0;
    pData->doc = 0;
    pData->notify = 0;
    pData->notifySignature = 0;

    static const char *kwlist[] = {"type", "fget", "fset", "freset", "fdel", "doc", "notify",
                                   "designable", "scriptable", "stored", "user",
                                   "constant", "final", 0};
    if (!PyArg_ParseTupleAndKeywords(args, kwds,
                                     "OO|OOOsObbbbbb:QtCore.QProperty", (char**) kwlist,
                                     /*OO*/     &type, &(pData->fget),
                                     /*OOO*/    &(pData->fset), &(pData->freset), &(pData->fdel),
                                     /*s*/      &(pData->doc),
                                     /*O*/      &(pData->notify),
                                     /*bbbbbb*/ &(pData->designable), &(pData->scriptable), &(pData->stored), &(pData->user), &(pData->constant), &(pData->final)))
        return 0;

    if (!pData->fset && pData->fget)
        pData->constant = true;

    pData->typeName = PySide::Signal::getTypeName(type);
    return 1;
}

void qpropertyFree(void *self)
{
    PyObject *pySelf = reinterpret_cast<PyObject*>(self);
    PySideProperty *data = reinterpret_cast<PySideProperty*>(self);

    free(data->d->typeName);
    free(data->d->doc);
    free(data->d->notifySignature);
    free(data->d);
    pySelf->ob_type->tp_base->tp_free(self);
}


} // extern "C"


namespace PySide { namespace Property {

void init(PyObject* module)
{
    if (PyType_Ready(&PySidePropertyType) < 0)
        return;

    Py_INCREF(&PySidePropertyType);
    PyModule_AddObject(module, QPROPERTY_CLASS_NAME, ((PyObject*)&PySidePropertyType));
}

bool isPropertyType(PyObject* pyObj)
{
    if (pyObj) {
        return pyObj->ob_type == &PySidePropertyType;
    }
    return false;
}

int setValue(PySideProperty* self, PyObject* source, PyObject* value)
{
    PyObject* fset = self->d->fset;
    if (fset) {
        Shiboken::AutoDecRef args(PyTuple_New(2));
        PyTuple_SET_ITEM(args, 0, source);
        PyTuple_SET_ITEM(args, 1, value);
        Py_INCREF(source);
        Py_INCREF(value);
        Shiboken::AutoDecRef result(PyObject_CallObject(fset, args));
        return (result.isNull() ? -1 : 0);
    } else {
        PyErr_SetString(PyExc_AttributeError, "Attibute read only");
    }
    return -1;
}

PyObject* getValue(PySideProperty* self, PyObject* source)
{
    PyObject* fget = self->d->fget;
    if (fget) {
        Shiboken::AutoDecRef args(PyTuple_New(1));
        Py_INCREF(source);
        PyTuple_SET_ITEM(args, 0, source);
        return  PyObject_CallObject(fget, args);
    }
    return 0;
}

int reset(PySideProperty* self, PyObject* source)
{
    PyObject* freset = self->d->freset;
    if (freset) {
        Shiboken::AutoDecRef args(PyTuple_New(1));
        Py_INCREF(source);
        PyTuple_SET_ITEM(args, 0, source);
        Shiboken::AutoDecRef result(PyObject_CallObject(freset, args));
        return (result.isNull() ? -1 : 0);
    }
    return -1;
}


const char* getTypeName(const PySideProperty* self)
{
    return self->d->typeName;
}

PySideProperty* getObject(PyObject* source, PyObject* name)
{
    PyObject* attr = PyObject_GenericGetAttr(source, name);
    if (attr && isPropertyType(attr))
        return reinterpret_cast<PySideProperty*>(attr);

    if (!attr)
        PyErr_Clear(); //Clear possible error caused by PyObject_GenericGetAttr
    else
        Py_DECREF(attr);
    return 0;
}

bool isReadable(const PySideProperty* self)
{
    return (self->d->fget != 0);
}

bool isWritable(const PySideProperty* self)
{
    return (self->d->fset != 0);
}

bool hasReset(const PySideProperty* self)
{
    return (self->d->freset != 0);
}

bool isDesignable(const PySideProperty* self)
{
    return self->d->designable;
}

bool isScriptable(const PySideProperty* self)
{
    return self->d->scriptable;
}

bool isStored(const PySideProperty* self)
{
    return self->d->stored;
}

bool isUser(const PySideProperty* self)
{
    return self->d->user;
}

bool isConstant(const PySideProperty* self)
{
    return self->d->constant;
}

bool isFinal(const PySideProperty* self)
{
    return self->d->final;
}

const char* getNotifyName(PySideProperty* self)
{
    if (!self->d->notifySignature) {
        PyObject* str = PyObject_Str(self->d->notify);
        self->d->notifySignature = strdup(PyString_AsString(str));
        Py_DECREF(str);
    }

    return self->d->notifySignature;
}

} //namespace Property
} //namespace PySide

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

#define QPROPERTY_CLASS_NAME "Property"

char* translateTypeName(PyObject* type)
{
    if (PyType_Check(type)) {
        char* typeName = 0;
        if (type->ob_type == &Shiboken::SbkBaseWrapperType_Type) {
            Shiboken::SbkBaseWrapperType* objType = reinterpret_cast<Shiboken::SbkBaseWrapperType*>(type);
            typeName = strdup(objType->original_name);
        } else {
            //tp_name return the full name
            Shiboken::AutoDecRef otypeName(PyObject_GetAttrString(type, "__name__"));
            typeName = strdup(PyString_AS_STRING(otypeName.object()));
        }
        if (Shiboken::TypeResolver::getType(typeName) == Shiboken::TypeResolver::ObjectType) {
            typeName = reinterpret_cast<char*>(realloc(typeName, strlen(typeName) + 1));
            typeName = strcat(typeName, "*");
        }
        return typeName;
    } else if (PyString_Check(type)) {
        return strdup(PyString_AS_STRING(type));
    }
    return 0;
}


extern "C"
{

struct PySideQPropertyDataPrivate {
    char* typeName;
    PyObject* type;
    PyObject* fget;
    PyObject* fset;
    PyObject* freset;
    PyObject* fdel;
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

PyTypeObject PySideQPropertyType = {
    PyObject_HEAD_INIT(0)
    0,                         /*ob_size*/
    QPROPERTY_CLASS_NAME,      /*tp_name*/
    sizeof(PySideQPropertyData), /*tp_basicsize*/
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
    PySideQPropertyData* data = reinterpret_cast<PySideQPropertyData*>(self);
    PySideQPropertyDataPrivate* pData = (PySideQPropertyDataPrivate*) malloc(sizeof(PySideQPropertyDataPrivate*));
    data->d = pData;
    pData->designable = true;
    pData->scriptable = true;
    pData->stored = true;

    static const char *kwlist[] = {"type", "fget", "fset", "freset", "fdel", "doc",
                                   "designable", "scriptable", "stored", "user",
                                   "constant", "final", 0};
    if (!PyArg_ParseTupleAndKeywords(args, kwds,
                                     "OO|OOOsbbbbbb:QtCore.QProperty", (char**) kwlist,
                                     /*OO*/     &type, &(pData->fget),
                                     /*OOOO*/   &(pData->fset), &(pData->freset), &(pData->fdel),
                                     /*s*/      &(pData->doc),
                                     /*bbbbbb*/ &(pData->designable), &(pData->scriptable), &(pData->stored), &(pData->user), &(pData->constant), &(pData->final)))
        return 0;

    if (!pData->fset && pData->fget)
        pData->constant = true;

    pData->typeName = translateTypeName(type);
    return 1;
}

void qpropertyFree(void *self)
{
    PyObject *pySelf = reinterpret_cast<PyObject*>(self);
    PySideQPropertyData *data = reinterpret_cast<PySideQPropertyData*>(self);

    free(data->d->typeName);
    free(data->d->doc);
    free(data->d);
    pySelf->ob_type->tp_base->tp_free(self);
}


} // extern "C"


namespace PySide
{

void initQProperty(PyObject* module)
{
    if (PyType_Ready(&PySideQPropertyType) < 0)
        return;

    Py_INCREF(&PySideQPropertyType);
    PyModule_AddObject(module, QPROPERTY_CLASS_NAME, ((PyObject*)&PySideQPropertyType));
}

bool isQPropertyType(PyObject* pyObj)
{
    if (pyObj) {
        return pyObj->ob_type == &PySideQPropertyType;
    }
    return false;
}

int qpropertySet(PyObject* self, PyObject* source, PyObject* value)
{
    PySideQPropertyData *data = reinterpret_cast<PySideQPropertyData*>(self);
    if (data->d->fset) {
        Shiboken::AutoDecRef args(PyTuple_New(2));
        PyTuple_SET_ITEM(args, 0, source);
        PyTuple_SET_ITEM(args, 1, value);
        Py_INCREF(source);
        Py_INCREF(value);
        Shiboken::AutoDecRef result(PyObject_CallObject(data->d->fset, args));
        return (result.isNull() ? -1 : 0);
    } else {
        PyErr_SetString(PyExc_AttributeError, "Attibute read only");
    }
    return -1;
}

PyObject* qpropertyGet(PyObject* self, PyObject* source)
{
    PySideQPropertyData *data = reinterpret_cast<PySideQPropertyData*>(self);
    if (data->d->fget) {
        Shiboken::AutoDecRef args(PyTuple_New(1));
        Py_INCREF(source);
        PyTuple_SET_ITEM(args, 0, source);
        return  PyObject_CallObject(data->d->fget, args);
    }
    return 0;
}

int qpropertyReset(PyObject* self, PyObject* source)
{
    PySideQPropertyData *data = reinterpret_cast<PySideQPropertyData*>(self);
    if (data->d->freset) {
        Shiboken::AutoDecRef args(PyTuple_New(1));
        Py_INCREF(source);
        PyTuple_SET_ITEM(args, 0, source);
        Shiboken::AutoDecRef result(PyObject_CallObject(data->d->freset, args));
        return (result.isNull() ? -1 : 0);
    }
    return -1;
}


const char* qpropertyGetType(PyObject* self)
{
    PySideQPropertyData *data = reinterpret_cast<PySideQPropertyData*>(self);
    return data->d->typeName;
}

PyObject* qpropertyGetObject(PyObject* source, PyObject* name)
{
    PyObject* attr = PyObject_GenericGetAttr(source, name);
    if (attr && isQPropertyType(attr))
        return attr;

    if (!attr)
        PyErr_Clear(); //Clear possible error caused by PyObject_GenericGetAttr
    else
        Py_DECREF(attr);
    return 0;
}

bool qpropertyIsReadable(PyObject* self)
{
    PySideQPropertyData *data = reinterpret_cast<PySideQPropertyData*>(self);
    return (data->d->fget != 0);
}

bool qpropertyIsWritable(PyObject* self)
{
    PySideQPropertyData *data = reinterpret_cast<PySideQPropertyData*>(self);
    return (data->d->fset != 0);
}

bool qpropertyHasReset(PyObject* self)
{
    PySideQPropertyData *data = reinterpret_cast<PySideQPropertyData*>(self);
    return (data->d->freset != 0);
}

bool qpropertyIsDesignable(PyObject* self)
{
    PySideQPropertyData *data = reinterpret_cast<PySideQPropertyData*>(self);
    return data->d->designable;
}

bool qpropertyIsScriptable(PyObject* self)
{
    PySideQPropertyData *data = reinterpret_cast<PySideQPropertyData*>(self);
    return data->d->scriptable;
}

bool qpropertyIsStored(PyObject* self)
{
    PySideQPropertyData *data = reinterpret_cast<PySideQPropertyData*>(self);
    return data->d->stored;
}

bool qpropertyIsUser(PyObject* self)
{
    PySideQPropertyData *data = reinterpret_cast<PySideQPropertyData*>(self);
    return data->d->user;
}

bool qpropertyIsConstant(PyObject* self)
{
    PySideQPropertyData *data = reinterpret_cast<PySideQPropertyData*>(self);
    return data->d->constant;
}

bool qpropertyIsFinal(PyObject* self)
{
    PySideQPropertyData *data = reinterpret_cast<PySideQPropertyData*>(self);
    return data->d->final;
}

} //namespace PySide

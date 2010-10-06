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

namespace PySide
{

// aux function
static char* translateTypeName(PyObject*);

extern "C"
{

typedef struct {
    PyObject_HEAD
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
} QPropertyData;

static int qpropertyTpInit(PyObject*, PyObject*, PyObject*);
static void qpropertyFree(void*);

PyTypeObject QProperty_Type = {
    PyObject_HEAD_INIT(0)
    0,                         /*ob_size*/
    QPROPERTY_CLASS_NAME,      /*tp_name*/
    sizeof(QPropertyData),     /*tp_basicsize*/
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
    qpropertyTpInit,             /*tp_init */
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

} // extern "C"

void initQProperty(PyObject* module)
{
    if (PyType_Ready(&QProperty_Type) < 0)
        return;

    Py_INCREF(&QProperty_Type);
    PyModule_AddObject(module, QPROPERTY_CLASS_NAME, ((PyObject*)&QProperty_Type));
}

int qpropertyTpInit(PyObject* self, PyObject* args, PyObject* kwds)
{
    PyObject* type = 0;
    QPropertyData *data = reinterpret_cast<QPropertyData*>(self);
    data->designable = true;
    data->scriptable = true;
    data->stored = true;

    static const char *kwlist[] = {"type", "fget", "fset", "freset", "fdel", "doc",
                                   "designable", "scriptable", "stored", "user",
                                   "constant", "final", 0};
    if (!PyArg_ParseTupleAndKeywords(args, kwds,
                                     "OO|OOOsbbbbbb:QtCore.QProperty", (char**) kwlist,
                                     /*OO*/     &type, &(data->fget),
                                     /*OOOO*/   &(data->fset), &(data->freset), &(data->fdel),
                                     /*s*/      &(data->doc),
                                     /*bbbbbb*/ &(data->designable), &(data->scriptable), &(data->stored), &(data->user), &(data->constant), &(data->final)))
        return 0;

    if (!data->fset && data->fget)
        data->constant = true;

    data->typeName = translateTypeName(type);
    return 1;
}

void qpropertyFree(void *self)
{
    PyObject *pySelf = reinterpret_cast<PyObject*>(self);
    QPropertyData *data = reinterpret_cast<QPropertyData*>(self);

    free(data->typeName);
    free(data->doc);

    pySelf->ob_type->tp_base->tp_free(self);
}

bool isQPropertyType(PyObject* pyObj)
{
    if (pyObj) {
        return pyObj->ob_type == &QProperty_Type;
    }
    return false;
}

int qpropertySet(PyObject* self, PyObject* source, PyObject* value)
{
    QPropertyData *data = reinterpret_cast<QPropertyData*>(self);
    if (data->fset) {
        Shiboken::AutoDecRef args(PyTuple_New(2));
        PyTuple_SET_ITEM(args, 0, source);
        PyTuple_SET_ITEM(args, 1, value);
        Py_INCREF(source);
        Py_INCREF(value);
        Shiboken::AutoDecRef result(PyObject_CallObject(data->fset, args));
        return (result.isNull() ? -1 : 0);
    } else {
        PyErr_SetString(PyExc_AttributeError, "Attibute read only");
    }
    return -1;
}

PyObject* qpropertyGet(PyObject* self, PyObject* source)
{
    QPropertyData *data = reinterpret_cast<QPropertyData*>(self);
    if (data->fget) {
        Shiboken::AutoDecRef args(PyTuple_New(1));
        Py_INCREF(source);
        PyTuple_SET_ITEM(args, 0, source);
        return  PyObject_CallObject(data->fget, args);
    }
    return 0;
}

int qpropertyReset(PyObject* self, PyObject* source)
{
    QPropertyData *data = reinterpret_cast<QPropertyData*>(self);
    if (data->freset) {
        Shiboken::AutoDecRef args(PyTuple_New(1));
        Py_INCREF(source);
        PyTuple_SET_ITEM(args, 0, source);
        Shiboken::AutoDecRef result(PyObject_CallObject(data->freset, args));
        return (result.isNull() ? -1 : 0);
    }
    return -1;
}


const char* qpropertyGetType(PyObject* self)
{
    QPropertyData *data = reinterpret_cast<QPropertyData*>(self);
    return data->typeName;
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

char* translateTypeName(PyObject* type)
{
    if (PyType_Check(type)) {
        char *typeName = NULL;
        if (type->ob_type == &Shiboken::SbkBaseWrapperType_Type) {
            Shiboken::SbkBaseWrapperType *objType = reinterpret_cast<Shiboken::SbkBaseWrapperType*>(type);
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

bool qpropertyIsReadable(PyObject* self)
{
    QPropertyData *data = reinterpret_cast<QPropertyData*>(self);
    return (data->fget != 0);
}

bool qpropertyIsWritable(PyObject* self)
{
    QPropertyData *data = reinterpret_cast<QPropertyData*>(self);
    return (data->fset != 0);
}

bool qpropertyHasReset(PyObject* self)
{
    QPropertyData *data = reinterpret_cast<QPropertyData*>(self);
    return (data->freset != 0);
}

bool qpropertyIsDesignable(PyObject* self)
{
    QPropertyData *data = reinterpret_cast<QPropertyData*>(self);
    return data->designable;
}

bool qpropertyIsScriptable(PyObject* self)
{
    QPropertyData *data = reinterpret_cast<QPropertyData*>(self);
    return data->scriptable;
}

bool qpropertyIsStored(PyObject* self)
{
    QPropertyData *data = reinterpret_cast<QPropertyData*>(self);
    return data->stored;
}

bool qpropertyIsUser(PyObject* self)
{
    QPropertyData *data = reinterpret_cast<QPropertyData*>(self);
    return data->user;
}

bool qpropertyIsConstant(PyObject* self)
{
    QPropertyData *data = reinterpret_cast<QPropertyData*>(self);
    return data->constant;
}

bool qpropertyIsFinal(PyObject* self)
{
    QPropertyData *data = reinterpret_cast<QPropertyData*>(self);
    return data->final;
}

} //namespace PySide

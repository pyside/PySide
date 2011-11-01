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
#include "pysideproperty.h"
#include "pysideproperty_p.h"
#include "dynamicqmetaobject_p.h"
#include "pysidesignal.h"
#include "pysidesignal_p.h"

#include <shiboken.h>
#include <QDebug>


#define QPROPERTY_CLASS_NAME "Property"

extern "C"
{

static PyObject* qpropertyTpNew(PyTypeObject* subtype, PyObject* args, PyObject* kwds);
static int qpropertyTpInit(PyObject*, PyObject*, PyObject*);
static void qpropertyFree(void*);

//methods
static PyObject* qPropertyCall(PyObject*, PyObject*, PyObject*);
static PyObject* qPropertySetter(PyObject*, PyObject*);
static PyObject* qPropertyGetter(PyObject*, PyObject*);

static PyMethodDef PySidePropertyMethods[] = {
    {"setter", (PyCFunction)qPropertySetter, METH_O},
    {"write", (PyCFunction)qPropertySetter, METH_O},
    {"getter", (PyCFunction)qPropertyGetter, METH_O},
    {"read", (PyCFunction)qPropertyGetter, METH_O},
    {0}
};

PyTypeObject PySidePropertyType = {
    PyVarObject_HEAD_INIT(0, 0)
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
    qPropertyCall,             /*tp_call*/
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
    PySidePropertyMethods,     /*tp_methods */
    0,                         /*tp_members */
    0,                         /*tp_getset */
    0,                         /*tp_base */
    0,                         /*tp_dict */
    0,                         /*tp_descr_get */
    0,                         /*tp_descr_set */
    0,                         /*tp_dictoffset */
    qpropertyTpInit,           /*tp_init */
    0,                         /*tp_alloc */
    qpropertyTpNew,            /*tp_new */
    qpropertyFree,             /*tp_free */
    0,                         /*tp_is_gc */
    0,                         /*tp_bases */
    0,                         /*tp_mro */
    0,                         /*tp_cache */
    0,                         /*tp_subclasses */
    0,                         /*tp_weaklist */
    0,                         /*tp_del */
};

static void qpropertyMetaCall(PySideProperty* pp, PyObject* self, QMetaObject::Call call, void** args)
{
    Shiboken::Conversions::SpecificConverter converter(pp->d->typeName);
    Q_ASSERT(converter);

    QByteArray type(pp->d->typeName);

    switch(call) {
        case QMetaObject::ReadProperty:
        {
            Shiboken::GilState gil;
            PyObject* value = PySide::Property::getValue(pp, self);
            if (value) {
                converter.toCpp(value, args[0]);
                Py_DECREF(value);
            } else if (PyErr_Occurred()) {
                PyErr_Print(); // Clear any errors but print them to stderr
            }
            break;
        }

        case QMetaObject::WriteProperty:
        {
            Shiboken::GilState gil;
            Shiboken::AutoDecRef value(converter.toPython(args[0]));
            PySide::Property::setValue(pp, self, value);
            break;
        }

        case QMetaObject::ResetProperty:
        {
            Shiboken::GilState gil;
            PySide::Property::reset(pp, self);
            break;
        }

        case QMetaObject::QueryPropertyDesignable:
        case QMetaObject::QueryPropertyScriptable:
        case QMetaObject::QueryPropertyStored:
        case QMetaObject::QueryPropertyEditable:
        case QMetaObject::QueryPropertyUser:
        // just to avoid gcc warnings
        case QMetaObject::InvokeMetaMethod:
        case QMetaObject::CreateInstance:
            break;
    }
}


static PyObject* qpropertyTpNew(PyTypeObject* subtype, PyObject* args, PyObject* kwds)
{
    PySideProperty* me = reinterpret_cast<PySideProperty*>(subtype->tp_alloc(subtype, 0));
    me->d = new PySidePropertyPrivate;
    memset(me->d, 0, sizeof(PySidePropertyPrivate));
    PySidePropertyPrivate* pData = me->d;
    pData->designable = true;
    pData->scriptable = true;
    pData->stored = true;
    return (PyObject*) me;
}

int qpropertyTpInit(PyObject* self, PyObject* args, PyObject* kwds)
{
    PyObject* type = 0;
    PySideProperty* data = reinterpret_cast<PySideProperty*>(self);
    PySidePropertyPrivate* pData = data->d;
    pData->metaCallHandler = &qpropertyMetaCall;

    static const char *kwlist[] = {"type", "fget", "fset", "freset", "fdel", "doc", "notify",
                                   "designable", "scriptable", "stored", "user",
                                   "constant", "final", 0};
    if (!PyArg_ParseTupleAndKeywords(args, kwds,
                                     "O|OOOOsObbbbbb:QtCore.QProperty", (char**) kwlist,
                                     /*OO*/     &type, &(pData->fget),
                                     /*OOO*/    &(pData->fset), &(pData->freset), &(pData->fdel),
                                     /*s*/      &(pData->doc),
                                     /*O*/      &(pData->notify),
                                     /*bbbbbb*/ &(pData->designable), &(pData->scriptable), &(pData->stored), &(pData->user), &(pData->constant), &(pData->final))) {
        return 0;
    }


    pData->typeName = PySide::Signal::getTypeName(type);

    if (!pData->typeName)
        PyErr_SetString(PyExc_TypeError, "Invalid property type or type name.");
    else if (pData->constant && (pData->fset || pData->notify))
        PyErr_SetString(PyExc_TypeError, "A constant property cannot have a WRITE method or a NOTIFY signal.");

    if (!PyErr_Occurred()) {
        Py_XINCREF(pData->fget);
        Py_XINCREF(pData->fset);
        Py_XINCREF(pData->freset);
        Py_XINCREF(pData->fdel);
        Py_XINCREF(pData->notify);
        return 1;
    } else {
        pData->fget = 0;
        pData->fset = 0;
        pData->freset = 0;
        pData->fdel = 0;
        pData->notify = 0;
        return -1;
    }
}

void qpropertyFree(void *self)
{
    PyObject *pySelf = reinterpret_cast<PyObject*>(self);
    PySideProperty *data = reinterpret_cast<PySideProperty*>(self);
    PySidePropertyPrivate* pData = data->d;

    Py_XDECREF(pData->fget);
    Py_XDECREF(pData->fset);
    Py_XDECREF(pData->freset);
    Py_XDECREF(pData->fdel);
    Py_XDECREF(pData->notify);

    free(pData->typeName);
    free(pData->doc);
    free(pData->notifySignature);
    delete data->d;
    pySelf->ob_type->tp_base->tp_free(self);
}

PyObject* qPropertyCall(PyObject* self, PyObject* args, PyObject* kw)
{
    PyObject *callback = PyTuple_GetItem(args, 0);
    if (PyFunction_Check(callback)) {
        PySideProperty *prop = reinterpret_cast<PySideProperty*>(self);
        PySidePropertyPrivate* pData = prop->d;

        Py_INCREF(callback);
        pData->fget = callback;

        Py_INCREF(self);
        return self;
    } else {
        PyErr_SetString(PyExc_TypeError, "Invalid property usage.");
        return 0;
    }
}

PyObject* qPropertySetter(PyObject* self, PyObject* callback)
{
    if (PyFunction_Check(callback)) {
        PySideProperty *prop = reinterpret_cast<PySideProperty*>(self);
        PySidePropertyPrivate* pData = prop->d;

        Py_INCREF(callback);
        pData->fset = callback;

        Py_INCREF(callback);
        return callback;
    } else {
        PyErr_SetString(PyExc_TypeError, "Invalid property setter agument.");
        return 0;
    }
}

PyObject* qPropertyGetter(PyObject* self, PyObject* callback)
{
    if (PyFunction_Check(callback)) {
        PySideProperty *prop = reinterpret_cast<PySideProperty*>(self);
        PySidePropertyPrivate* pData = prop->d;

        Py_INCREF(callback);
        pData->fget = callback;

        Py_INCREF(callback);
        return callback;
    } else {
        PyErr_SetString(PyExc_TypeError, "Invalid property getter agument.");
        return 0;
    }
}

} // extern "C"

namespace {

static PyObject* getFromType(PyTypeObject* type, PyObject* name)
{
    PyObject* attr = 0;
    attr = PyDict_GetItem(type->tp_dict, name);
    if (!attr) {
        PyObject* bases = type->tp_bases;
        int size = PyTuple_GET_SIZE(bases);
        for(int i=0; i < size; i++) {
            PyObject* base = PyTuple_GET_ITEM(bases, i);
            attr = getFromType(reinterpret_cast<PyTypeObject*>(base), name);
            if (attr)
                return attr;
        }
    }
    return attr;
}

} //namespace


namespace PySide { namespace Property {

void init(PyObject* module)
{
    if (PyType_Ready(&PySidePropertyType) < 0)
        return;

    Py_INCREF(&PySidePropertyType);
    PyModule_AddObject(module, QPROPERTY_CLASS_NAME, ((PyObject*)&PySidePropertyType));
}

bool checkType(PyObject* pyObj)
{
    if (pyObj) {
        return PyType_IsSubtype(pyObj->ob_type, &PySidePropertyType);
    }
    return false;
}

bool isPropertyType(PyObject* pyObj)
{
    return checkType(pyObj);
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
    PyObject* attr = 0;

    if (Shiboken::Object::isUserType(source)) {
        PyObject* dict = reinterpret_cast<SbkObject*>(source)->ob_dict;
        if (dict)
            attr = PyDict_GetItem(dict, name);
    }

    attr = getFromType(source->ob_type, name);
    if (attr && checkType(attr)) {
        Py_INCREF(attr);
        return reinterpret_cast<PySideProperty*>(attr);
    }

    if (!attr)
        PyErr_Clear(); //Clear possible error caused by PyObject_GenericGetAttr

    return 0;
}

bool isReadable(const PySideProperty* self)
{
    return true;
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
        self->d->notifySignature = strdup(Shiboken::String::toCString(str));
        Py_DECREF(str);
    }

    return self->d->notifySignature;
}

void setMetaCallHandler(PySideProperty* self, MetaCallHandler handler)
{
    self->d->metaCallHandler = handler;
}

void setTypeName(PySideProperty* self, const char* typeName)
{
    self->d->typeName = strdup(typeName);
}

void setUserData(PySideProperty* self, void* data)
{
    self->d->userData = data;
}

void* userData(PySideProperty* self)
{
    return self->d->userData;
}

} //namespace Property
} //namespace PySide

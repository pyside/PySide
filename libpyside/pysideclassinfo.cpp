/*
 * This file is part of the PySide project.
 *
 * Copyright (C) 2009-2011 Nokia Corporation and/or its subsidiary(-ies).
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
#include "pysideclassinfo.h"
#include "pysideclassinfo_p.h"
#include "dynamicqmetaobject.h"

#include <shiboken.h>
#include <QDebug>

#define CLASSINFO_CLASS_NAME    "ClassInfo"

extern "C"
{

static PyObject* classInfoTpNew(PyTypeObject* subtype, PyObject* args, PyObject* kwds);
static int classInfoTpInit(PyObject*, PyObject*, PyObject*);
static void classInfoFree(void*);
static PyObject* classCall(PyObject*, PyObject*, PyObject*);

PyTypeObject PySideClassInfoType = {
    PyVarObject_HEAD_INIT(0, 0)
    CLASSINFO_CLASS_NAME,      /*tp_name*/
    sizeof(PySideClassInfo),   /*tp_basicsize*/
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
    classCall,                 /*tp_call*/
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
    classInfoTpInit,           /*tp_init */
    0,                         /*tp_alloc */
    classInfoTpNew,            /*tp_new */
    classInfoFree,             /*tp_free */
    0,                         /*tp_is_gc */
    0,                         /*tp_bases */
    0,                         /*tp_mro */
    0,                         /*tp_cache */
    0,                         /*tp_subclasses */
    0,                         /*tp_weaklist */
    0,                         /*tp_del */
};

PyObject* classCall(PyObject* self, PyObject* args, PyObject* kw)
{
    PyObject* klass;
    klass = PyTuple_GetItem(args, 0);

    if (Shiboken::ObjectType::checkType(reinterpret_cast<PyTypeObject*>(klass))) {
        PySide::DynamicQMetaObject* mo = reinterpret_cast<PySide::DynamicQMetaObject*>(Shiboken::ObjectType::getTypeUserData(reinterpret_cast<SbkObjectType*>(klass)));
        if (mo)
            mo->addInfo(PySide::ClassInfo::getMap(reinterpret_cast<PySideClassInfo*>(self)));
    }

    Py_INCREF(klass);
    return klass;
}

static PyObject* classInfoTpNew(PyTypeObject* subtype, PyObject* args, PyObject* kwds)
{
    PySideClassInfo* me = reinterpret_cast<PySideClassInfo*>(subtype->tp_alloc(subtype, 0));
    me->d = new PySideClassInfoPrivate;
    return (PyObject*) me;
}

int classInfoTpInit(PyObject* self, PyObject* args, PyObject* kwds)
{
    PySideClassInfo* data = reinterpret_cast<PySideClassInfo*>(self);
    PySideClassInfoPrivate* pData = data->d;

    PyObject* key;
    PyObject* value;
    Py_ssize_t pos = 0;
    while (PyDict_Next(kwds, &pos, &key, &value)) {
        if (Shiboken::String::check(key) && Shiboken::String::check(value))
            pData->m_data[Shiboken::String::toCString(key)] = Shiboken::String::toCString(value);
    }

    return PyErr_Occurred() ? -1 : 1;
}

void classInfoFree(void *self)
{
    PyObject* pySelf = reinterpret_cast<PyObject*>(self);
    PySideClassInfo* data = reinterpret_cast<PySideClassInfo*>(self);

    delete data->d;
    pySelf->ob_type->tp_base->tp_free(self);
}


} // extern "C"


namespace PySide { namespace ClassInfo {

void init(PyObject* module)
{
    if (PyType_Ready(&PySideClassInfoType) < 0)
        return;

    Py_INCREF(&PySideClassInfoType);
    PyModule_AddObject(module, CLASSINFO_CLASS_NAME, ((PyObject*)&PySideClassInfoType));
}

bool checkType(PyObject* pyObj)
{
    if (pyObj)
        return PyType_IsSubtype(pyObj->ob_type, &PySideClassInfoType);
    return false;
}

QMap<QByteArray, QByteArray> getMap(PySideClassInfo* obj)
{
    return obj->d->m_data;
}

} //namespace Property
} //namespace PySide

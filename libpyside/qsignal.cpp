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

#include <shiboken.h>
#include <Python.h>
#include <QDebug>

#include "qsignal.h"
#include "signalmanager.h"

#define SIGNAL_CLASS_NAME "Signal"
#define QT_SIGNAL_SENTINEL "2"

namespace PySide
{

extern "C"
{

typedef struct {
    PyObject_HEAD
    bool initialized;
    char* signalName;
    char** signatures;
    int signaturesSize;
} SignalData;

static int signal_init(PyObject*, PyObject*, PyObject*);
static void signal_free(void*);
static void signal_instance_free(void*);

//methods
static PyObject* signal_instance_connect(PyObject*, PyObject*, PyObject*);
static PyObject* signal_instance_disconnect(PyObject*, PyObject*);
static PyObject* signal_instance_emit(PyObject*, PyObject*);
static PyObject* signal_instance_get_item(PyObject*, PyObject*);

//aux
static char* signal_build_signature(const char*, const char*);
static char* signal_get_type_name(PyObject*);
static void signal_append_signature(SignalData*, char*);
static void signal_instance_initialize(PyObject*, PyObject*, SignalData*, PyObject *, int);
static char* signal_parse_signature(PyObject*);
static PyObject* signal_build_qt_compatible(const char*);

PyTypeObject Signal_Type = {
    PyObject_HEAD_INIT(0)
    0,                         /*ob_size*/
    SIGNAL_CLASS_NAME,         /*tp_name*/
    sizeof(SignalData),        /*tp_basicsize*/
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
    SIGNAL_CLASS_NAME,         /*tp_doc */
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
    (initproc)signal_init,    /*tp_init */
    0,                         /*tp_alloc */
    PyType_GenericNew,         /*tp_new */
    signal_free,              /*tp_free */
    0,                         /*tp_is_gc */
    0,                         /*tp_bases */
    0,                         /*tp_mro */
    0,                         /*tp_cache */
    0,                         /*tp_subclasses */
    0,                         /*tp_weaklist */
    0,                         /*tp_del */
};

static PyMethodDef SignalInstance_methods[] = {
    {"connect", (PyCFunction)signal_instance_connect, METH_VARARGS|METH_KEYWORDS},
    {"disconnect", (PyCFunction)signal_instance_disconnect, METH_VARARGS},
    {"emit", (PyCFunction)signal_instance_emit, METH_VARARGS},
    {NULL}  /* Sentinel */
};

static PyMappingMethods SignalInstance_as_mapping = {
    0,
    signal_instance_get_item,
    0
};

PyTypeObject SignalInstance_Type = {
    PyObject_HEAD_INIT(0)
    0,                         /*ob_size*/
    SIGNAL_CLASS_NAME,         /*tp_name*/
    sizeof(SignalInstanceData),/*tp_basicsize*/
    0,                         /*tp_itemsize*/
    0,                         /*tp_dealloc*/
    0,                         /*tp_print*/
    0,                         /*tp_getattr*/
    0,                         /*tp_setattr*/
    0,                         /*tp_compare*/
    0,                         /*tp_repr*/
    0,                         /*tp_as_number*/
    0,                         /*tp_as_sequence*/
    &SignalInstance_as_mapping,/*tp_as_mapping*/
    0,                         /*tp_hash */
    0,                         /*tp_call*/
    0,                         /*tp_str*/
    0,                         /*tp_getattro*/
    0,                         /*tp_setattro*/
    0,                         /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT,        /*tp_flags*/
    SIGNAL_CLASS_NAME,         /*tp_doc */
    0,                         /*tp_traverse */
    0,                         /*tp_clear */
    0,                         /*tp_richcompare */
    0,                         /*tp_weaklistoffset */
    0,                         /*tp_iter */
    0,                         /*tp_iternext */
    SignalInstance_methods,    /*tp_methods */
    0,                         /*tp_members */
    0,                         /*tp_getset */
    0,                         /*tp_base */
    0,                         /*tp_dict */
    0,                         /*tp_descr_get */
    0,                         /*tp_descr_set */
    0,                         /*tp_dictoffset */
    0,                         /*tp_init */
    0,                         /*tp_alloc */
    PyType_GenericNew,         /*tp_new */
    signal_instance_free,     /*tp_free */
    0,                         /*tp_is_gc */
    0,                         /*tp_bases */
    0,                         /*tp_mro */
    0,                         /*tp_cache */
    0,                         /*tp_subclasses */
    0,                         /*tp_weaklist */
    0,                         /*tp_del */
};


void init_signal(PyObject* module)
{
    if (PyType_Ready(&Signal_Type) < 0)
        return;

    Py_INCREF(&Signal_Type);
    PyModule_AddObject(module, SIGNAL_CLASS_NAME, ((PyObject*)&Signal_Type));

    if (PyType_Ready(&SignalInstance_Type) < 0)
        return;

    Py_INCREF(&SignalInstance_Type);
}


} // extern "C"


PyObject* signal_instance_get_item(PyObject* self, PyObject* key)
{
    SignalInstanceData* data = reinterpret_cast<SignalInstanceData*>(self);
    char* sigKey = signal_parse_signature(key);
    char* sig = signal_build_signature(data->signalName, sigKey);
    free(sigKey);

    while(data) {
        if (strcmp(data->signature, sig) == 0) {
            free(sig);
            PyObject *result = reinterpret_cast<PyObject*>(data);
            Py_INCREF(result);
            return result;
        }
        data = reinterpret_cast<SignalInstanceData*>(data->next);
    }
    free(sig);
    return 0;
}

void signalUpdateSource(PyObject* source)
{
    Shiboken::AutoDecRef attrs(PyObject_Dir(source));

    for(int i = 0, i_max = PyList_GET_SIZE(attrs.object()); i < i_max; i++) {
        PyObject *attrName = PyList_GET_ITEM(attrs.object(), i);
        Shiboken::AutoDecRef attr(PyObject_GetAttr((PyObject*)source->ob_type, attrName));
        if (!attr.isNull() && (attr->ob_type == &Signal_Type)) {
            Shiboken::AutoDecRef signalInstance(reinterpret_cast<PyObject*>(PyObject_New(SignalInstanceData, &SignalInstance_Type)));
            signal_instance_initialize(signalInstance, attrName, reinterpret_cast<SignalData*>(attr.object()), source, 0);
            PyObject_SetAttr(source, attrName, signalInstance);
        }
    }
}

char* signal_get_type_name(PyObject* type)
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

char* signal_build_signature(const char *name, const char *signature)
{
    QString signal;
    signal.sprintf("%s(%s)", name, signature);
    return strdup(QMetaObject::normalizedSignature(signal.toAscii()));
}

char* signal_parse_signature(PyObject *args)
{
    char *signature = 0;

    if (args && (PyString_Check(args) || (!PySequence_Check(args) && (args != Py_None))))
        return signal_get_type_name(args);

    for(Py_ssize_t i = 0, i_max = PySequence_Size(args); i < i_max; i++) {
        Shiboken::AutoDecRef arg(PySequence_ITEM(args, i));
        char* typeName = signal_get_type_name(arg);
        if (typeName) {
            if (signature) {
                signature = reinterpret_cast<char*>(realloc(signature, (strlen(signature) + 1 + strlen(typeName)) * sizeof(char*)));
                signature = strcat(signature, ",");
                signature = strcat(signature, typeName);
                free(typeName);
            } else {
                signature = typeName;
            }
        }
    }
    return signature;
}

void signal_append_signature(SignalData* self, char* signature)
{
    self->signaturesSize++;

    if (self->signaturesSize > 1) {
        self->signatures = (char**) realloc(self->signatures, sizeof(char**) * self->signaturesSize);
    } else {
        self->signatures = (char**) malloc(sizeof(char**));
    }
    self->signatures[self->signaturesSize-1] = signature;
}

int signal_init(PyObject* self, PyObject* args, PyObject* kwds)
{
    static PyObject *emptyTuple = 0;
    static const char *kwlist[] = {"name", 0};
    char* argName = 0;

    if (emptyTuple == 0)
        emptyTuple = PyTuple_New(0);

    if (!PyArg_ParseTupleAndKeywords(emptyTuple, kwds,
                                     "|s:QtCore."SIGNAL_CLASS_NAME, (char**) kwlist, &argName))
        return 0;

    bool tupledArgs = false;
    SignalData *data = reinterpret_cast<SignalData*>(self);
    if (argName) {
        data->signalName = strdup(argName);
    }

    for(Py_ssize_t i = 0, i_max = PyTuple_Size(args); i < i_max; i++) {
        PyObject *arg = PyTuple_GET_ITEM(args, i);
        if (PySequence_Check(arg) && !PyString_Check(arg)) {
            tupledArgs = true;
            signal_append_signature(data, signal_parse_signature(arg));
        }
    }

    if (!tupledArgs)
        signal_append_signature(data, signal_parse_signature(args));

    return 1;
}

void signal_free(void *self)
{
    PyObject *pySelf = reinterpret_cast<PyObject*>(self);
    SignalData *data = reinterpret_cast<SignalData*>(self);

    for(int i = 0, i_max = data->signaturesSize; i < i_max; i++) {
        if (data->signatures[i])
            free(data->signatures[i]);
    }

    free(data->signatures);
    free(data->signalName);
    data->initialized = 0;
    data->signaturesSize = 0;

    pySelf->ob_type->tp_base->tp_free(self);
}

void signal_instance_free(void* self)
{
    PyObject *pySelf = reinterpret_cast<PyObject*>(self);
    SignalInstanceData *data = reinterpret_cast<SignalInstanceData*>(self);

    free(data->signalName);
    free(data->signature);

    while(data) {
        Py_XDECREF(data->next);
        data = reinterpret_cast<SignalInstanceData*>(data->next);
    }
    pySelf->ob_type->tp_base->tp_free(self);
}

void signal_instance_initialize(PyObject* instance, PyObject* name, SignalData* data, PyObject* source, int index)
{
    SignalInstanceData *self = reinterpret_cast<SignalInstanceData*>(instance);
    self->next = 0;
    if (data->signalName)
        self->signalName = strdup(data->signalName);
    else
        self->signalName = strdup(PyString_AsString(name));

    self->source = source;
    self->signature = signal_build_signature(self->signalName, data->signatures[index]);
    index++;

    if (index < data->signaturesSize) {
        self->next = reinterpret_cast<PyObject*>(PyObject_New(SignalInstanceData, &SignalInstance_Type));
        signal_instance_initialize(self->next, name, data, source, index);
    }
}

PyObject* signal_instance_connect(PyObject* self, PyObject* args, PyObject* kwds)
{
    PyObject *slot = 0;
    PyObject *type = 0;
    static const char *kwlist[] = {"slot", "type", 0};

    if (!PyArg_ParseTupleAndKeywords(args, kwds,
                                     "O|O:"SIGNAL_CLASS_NAME, (char**) kwlist, &slot, &type))
        return 0;

    SignalInstanceData *source = reinterpret_cast<SignalInstanceData*>(self);
    Shiboken::AutoDecRef pyArgs(PyList_New(0));

    bool match = false;
    if (slot->ob_type == &SignalInstance_Type) {
        SignalInstanceData *sourceWalk = source;
        SignalInstanceData *targetWalk;

        //find best match
        while(sourceWalk && !match) {
            targetWalk = reinterpret_cast<SignalInstanceData*>(slot);
            while(targetWalk && !match) {
                if (QMetaObject::checkConnectArgs(sourceWalk->signature, targetWalk->signature)) {
                    PyList_Append(pyArgs, sourceWalk->source);
                    Shiboken::AutoDecRef sourceSignature(signal_build_qt_compatible(sourceWalk->signature));
                    PyList_Append(pyArgs, sourceSignature);

                    PyList_Append(pyArgs, targetWalk->source);
                    Shiboken::AutoDecRef targetSignature(signal_build_qt_compatible(targetWalk->signature));
                    PyList_Append(pyArgs, targetSignature);

                    match = true;
                }
                targetWalk = reinterpret_cast<SignalInstanceData*>(targetWalk->next);
            }
            sourceWalk = reinterpret_cast<SignalInstanceData*>(sourceWalk->next);
        }
    } else {
        //try the first signature
        PyList_Append(pyArgs, source->source);
        Shiboken::AutoDecRef signature(signal_build_qt_compatible(source->signature));
        PyList_Append(pyArgs, signature);

        PyList_Append(pyArgs, slot);
        match = true;
    }

    if (type)
        PyList_Append(pyArgs, type);

    if (match) {
        Shiboken::AutoDecRef tupleArgs(PyList_AsTuple(pyArgs));
        Shiboken::AutoDecRef pyMethod(PyObject_GetAttrString(source->source, "connect"));
        return  PyObject_CallObject(pyMethod, tupleArgs);
    }

    return 0;
}

PyObject* signal_instance_disconnect(PyObject* self, PyObject* args)
{
    SignalInstanceData *source = reinterpret_cast<SignalInstanceData*>(self);
    Shiboken::AutoDecRef pyArgs(PyList_New(0));

    PyObject *slot;
    if PyTuple_Check(args)
        slot = PyTuple_GET_ITEM(args, 0);
    else
        slot = args;

    bool match = false;
    if (slot->ob_type == &SignalInstance_Type) {
        SignalInstanceData *target = reinterpret_cast<SignalInstanceData*>(slot);
        if (QMetaObject::checkConnectArgs(source->signature, target->signature)) {
            PyList_Append(pyArgs, source->source);
            Shiboken::AutoDecRef source_signature(signal_build_qt_compatible(source->signature));
            PyList_Append(pyArgs, source_signature);

            PyList_Append(pyArgs, target->source);
            Shiboken::AutoDecRef target_signature(signal_build_qt_compatible(target->signature));
            PyList_Append(pyArgs, target_signature);
            match = true;
        }
    } else {
        //try the first signature
        PyList_Append(pyArgs, source->source);
        Shiboken::AutoDecRef signature(signal_build_qt_compatible(source->signature));
        PyList_Append(pyArgs, signature);

        PyList_Append(pyArgs, slot);
        match = true;
    }

    if (match) {
        Shiboken::AutoDecRef tupleArgs(PyList_AsTuple(pyArgs));
        Shiboken::AutoDecRef pyMethod(PyObject_GetAttrString(source->source, "disconnect"));
        return  PyObject_CallObject(pyMethod, tupleArgs);
    }

    return 0;
}

PyObject* signal_instance_emit(PyObject* self, PyObject* args)
{
    SignalInstanceData *source = reinterpret_cast<SignalInstanceData*>(self);

    Shiboken::AutoDecRef pyArgs(PyList_New(0));
    Shiboken::AutoDecRef source_signature(signal_build_qt_compatible(source->signature));

    PyList_Append(pyArgs, source_signature);
    for(Py_ssize_t i=0, i_max=PyTuple_Size(args); i < i_max; i++)
        PyList_Append(pyArgs, PyTuple_GetItem(args, i));

    Shiboken::AutoDecRef pyMethod(PyObject_GetAttrString(source->source, "emit"));

    Shiboken::AutoDecRef tupleArgs(PyList_AsTuple(pyArgs));
    return PyObject_CallObject(pyMethod, tupleArgs);
}

PyObject* signalNew(const char* name, ...)
{
    va_list listSignatures;
    char* sig = 0;
    SignalData* self = PyObject_New(SignalData, &Signal_Type);
    self->signalName = strdup(name);
    self->signaturesSize = 0;
    self->signatures = 0;
    self->initialized = 0;

    va_start(listSignatures, name);
    sig = va_arg(listSignatures, char*);

    while(sig != NULL) {
        signal_append_signature(self, strdup(sig));
        sig = va_arg(listSignatures, char*);
    }

    va_end(listSignatures);

    return reinterpret_cast<PyObject*>(self);
}


PyObject* signal_build_qt_compatible(const char* signature)
{
    char* qtSignature;
    qtSignature = reinterpret_cast<char*>(malloc(strlen(signature)+2));
    sprintf(qtSignature, QT_SIGNAL_SENTINEL"%s", signature);
    PyObject* ret = PyString_FromString(qtSignature);
    free(qtSignature);
    return ret;
}


} //namespace PySide

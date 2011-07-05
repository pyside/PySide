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
#include <Python.h>
#include "pysidesignal.h"
#include "pysidesignal_p.h"
#include "signalmanager.h"

#include <shiboken.h>
#include <QDebug>

#define SIGNAL_CLASS_NAME "Signal"
#define QT_SIGNAL_SENTINEL '2'


namespace PySide { namespace Signal {
    //aux
    static char*        buildSignature(const char*, const char*);
    static void         appendSignature(PySideSignal*, char*);
    static void         instanceInitialize(PySideSignalInstance*, PyObject*, PySideSignal*, PyObject *, int);
    static char*        parseSignature(PyObject*);
    static PyObject*    buildQtCompatible(const char*);
}
}

extern "C"
{

//Signal methods
static int signalTpInit(PyObject*, PyObject*, PyObject*);
static void signalFree(void*);
static void signalInstanceFree(void*);
static PyObject* signalGetItem(PyObject* self, PyObject* key);
static PyObject* signalToString(PyObject* self);

//Signal Instance methods
static PyObject* signalInstanceConnect(PyObject*, PyObject*, PyObject*);
static PyObject* signalInstanceDisconnect(PyObject*, PyObject*);
static PyObject* signalInstanceEmit(PyObject*, PyObject*);
static PyObject* signalInstanceGetItem(PyObject*, PyObject*);

static PyObject* signalInstanceCall(PyObject* self, PyObject* args, PyObject* kw);
static PyObject* signalCall(PyObject*, PyObject*, PyObject*);

static PyMappingMethods Signal_as_mapping = {
    0,
    signalGetItem,
    0
};


PyTypeObject PySideSignalType = {
    PyObject_HEAD_INIT(0)
    /*ob_size*/             0,
    /*tp_name*/             "PySide.QtCore."SIGNAL_CLASS_NAME,
    /*tp_basicsize*/        sizeof(PySideSignal),
    /*tp_itemsize*/         0,
    /*tp_dealloc*/          0,
    /*tp_print*/            0,
    /*tp_getattr*/          0,
    /*tp_setattr*/          0,
    /*tp_compare*/          0,
    /*tp_repr*/             0,
    /*tp_as_number*/        0,
    /*tp_as_sequence*/      0,
    /*tp_as_mapping*/       &Signal_as_mapping,
    /*tp_hash*/             0,
    /*tp_call*/             signalCall,
    /*tp_str*/              signalToString,
    /*tp_getattro*/         0,
    /*tp_setattro*/         0,
    /*tp_as_buffer*/        0,
    /*tp_flags*/            Py_TPFLAGS_DEFAULT,
    /*tp_doc*/              SIGNAL_CLASS_NAME,
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
    /*tp_init*/             signalTpInit,
    /*tp_alloc*/            0,
    /*tp_new*/              PyType_GenericNew,
    /*tp_free*/             signalFree,
    /*tp_is_gc*/            0,
    /*tp_bases*/            0,
    /*tp_mro*/              0,
    /*tp_cache*/            0,
    /*tp_subclasses*/       0,
    /*tp_weaklist*/         0,
    /*tp_del*/              0,
};

static PyMethodDef SignalInstance_methods[] = {
    {"connect", (PyCFunction)signalInstanceConnect, METH_VARARGS|METH_KEYWORDS, 0},
    {"disconnect", signalInstanceDisconnect, METH_VARARGS, 0},
    {"emit", signalInstanceEmit, METH_VARARGS, 0},
    {0}  /* Sentinel */
};

static PyMappingMethods SignalInstance_as_mapping = {
    0,
    signalInstanceGetItem,
    0
};

PyTypeObject PySideSignalInstanceType = {
    PyObject_HEAD_INIT(0)
    /*ob_size*/             0,
    /*tp_name*/             "PySide.QtCore."SIGNAL_CLASS_NAME,
    /*tp_basicsize*/        sizeof(PySideSignalInstance),
    /*tp_itemsize*/         0,
    /*tp_dealloc*/          0,
    /*tp_print*/            0,
    /*tp_getattr*/          0,
    /*tp_setattr*/          0,
    /*tp_compare*/          0,
    /*tp_repr*/             0,
    /*tp_as_number*/        0,
    /*tp_as_sequence*/      0,
    /*tp_as_mapping*/       &SignalInstance_as_mapping,
    /*tp_hash*/             0,
    /*tp_call*/             signalInstanceCall,
    /*tp_str*/              0,
    /*tp_getattro*/         0,
    /*tp_setattro*/         0,
    /*tp_as_buffer*/        0,
    /*tp_flags*/            Py_TPFLAGS_DEFAULT,
    /*tp_doc*/              SIGNAL_CLASS_NAME,
    /*tp_traverse*/         0,
    /*tp_clear*/            0,
    /*tp_richcompare*/      0,
    /*tp_weaklistoffset*/   0,
    /*tp_iter*/             0,
    /*tp_iternext*/         0,
    /*tp_methods*/          SignalInstance_methods,
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
    /*tp_free*/             signalInstanceFree,
    /*tp_is_gc*/            0,
    /*tp_bases*/            0,
    /*tp_mro*/              0,
    /*tp_cache*/            0,
    /*tp_subclasses*/       0,
    /*tp_weaklist*/         0,
    /*tp_del*/              0,
};

int signalTpInit(PyObject* self, PyObject* args, PyObject* kwds)
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
    PySideSignal *data = reinterpret_cast<PySideSignal*>(self);
    if (argName) {
        data->signalName = strdup(argName);
    }

    for(Py_ssize_t i = 0, i_max = PyTuple_Size(args); i < i_max; i++) {
        PyObject *arg = PyTuple_GET_ITEM(args, i);
        if (PySequence_Check(arg) && !PyString_Check(arg)) {
            tupledArgs = true;
            PySide::Signal::appendSignature(data, PySide::Signal::parseSignature(arg));
        }
    }

    if (!tupledArgs)
        PySide::Signal::appendSignature(data, PySide::Signal::parseSignature(args));

    return 1;
}

void signalFree(void *self)
{
    PyObject *pySelf = reinterpret_cast<PyObject*>(self);
    PySideSignal *data = reinterpret_cast<PySideSignal*>(self);

    for(int i = 0, i_max = data->signaturesSize; i < i_max; i++) {
        if (data->signatures[i])
            free(data->signatures[i]);
    }

    free(data->signatures);
    free(data->signalName);
    data->initialized = 0;
    data->signaturesSize = 0;
    Py_XDECREF(data->homonymousMethod);
    data->homonymousMethod = 0;

    pySelf->ob_type->tp_base->tp_free(self);
}

PyObject* signalGetItem(PyObject* self, PyObject* key)
{
    PySideSignal* data = reinterpret_cast<PySideSignal*>(self);
    char* sigKey;
    if (key) {
        sigKey = PySide::Signal::parseSignature(key);
    } else {
        if (data->signatures[0])
            sigKey = strdup(data->signatures[0]);
        else
            sigKey = strdup("void");
    }
    char* sig = PySide::Signal::buildSignature(data->signalName, sigKey);
    free(sigKey);
    PyObject* pySignature = PyString_FromString(sig);
    free(sig);
    return pySignature;
}


PyObject* signalToString(PyObject* self)
{
    return signalGetItem(self, 0);
}

void signalInstanceFree(void* self)
{
    PyObject* pySelf = reinterpret_cast<PyObject*>(self);
    PySideSignalInstance* data = reinterpret_cast<PySideSignalInstance*>(self);

    PySideSignalInstancePrivate* dataPvt = data->d;
    free(dataPvt->signalName);
    free(dataPvt->signature);

    Py_XDECREF(dataPvt->homonymousMethod);

    if (dataPvt->next) {
        Py_DECREF(dataPvt->next);
        dataPvt->next = 0;
    }
    delete dataPvt;
    data->d = 0;
    pySelf->ob_type->tp_base->tp_free(self);
}

PyObject* signalInstanceConnect(PyObject* self, PyObject* args, PyObject* kwds)
{
    PyObject *slot = 0;
    PyObject *type = 0;
    static const char *kwlist[] = {"slot", "type", 0};

    if (!PyArg_ParseTupleAndKeywords(args, kwds,
        "O|O:"SIGNAL_CLASS_NAME, (char**) kwlist, &slot, &type))
        return 0;

    PySideSignalInstance *source = reinterpret_cast<PySideSignalInstance*>(self);
    Shiboken::AutoDecRef pyArgs(PyList_New(0));

    bool match = false;
    if (slot->ob_type == &PySideSignalInstanceType) {
        PySideSignalInstance *sourceWalk = source;
        PySideSignalInstance *targetWalk;

        //find best match
        while(sourceWalk && !match) {
            targetWalk = reinterpret_cast<PySideSignalInstance*>(slot);
            while(targetWalk && !match) {
                if (QMetaObject::checkConnectArgs(sourceWalk->d->signature, targetWalk->d->signature)) {
                    PyList_Append(pyArgs, sourceWalk->d->source);
                    Shiboken::AutoDecRef sourceSignature(PySide::Signal::buildQtCompatible(sourceWalk->d->signature));
                    PyList_Append(pyArgs, sourceSignature);

                    PyList_Append(pyArgs, targetWalk->d->source);
                    Shiboken::AutoDecRef targetSignature(PySide::Signal::buildQtCompatible(targetWalk->d->signature));
                    PyList_Append(pyArgs, targetSignature);

                    match = true;
                }
                targetWalk = reinterpret_cast<PySideSignalInstance*>(targetWalk->d->next);
            }
            sourceWalk = reinterpret_cast<PySideSignalInstance*>(sourceWalk->d->next);
        }
    } else {
        //try the first signature
        PyList_Append(pyArgs, source->d->source);
        Shiboken::AutoDecRef signature(PySide::Signal::buildQtCompatible(source->d->signature));
        PyList_Append(pyArgs, signature);

        PyList_Append(pyArgs, slot);
        match = true;
    }

    if (type)
        PyList_Append(pyArgs, type);

    if (match) {
        Shiboken::AutoDecRef tupleArgs(PyList_AsTuple(pyArgs));
        Shiboken::AutoDecRef pyMethod(PyObject_GetAttrString(source->d->source, "connect"));
        return PyObject_CallObject(pyMethod, tupleArgs);
    }

    return 0;
}

PyObject* signalInstanceEmit(PyObject* self, PyObject* args)
{
    PySideSignalInstance *source = reinterpret_cast<PySideSignalInstance*>(self);

    Shiboken::AutoDecRef pyArgs(PyList_New(0));
    Shiboken::AutoDecRef sourceSignature(PySide::Signal::buildQtCompatible(source->d->signature));

    PyList_Append(pyArgs, sourceSignature);
    for(Py_ssize_t i = 0, max = PyTuple_Size(args); i < max; i++)
        PyList_Append(pyArgs, PyTuple_GetItem(args, i));

    Shiboken::AutoDecRef pyMethod(PyObject_GetAttrString(source->d->source, "emit"));

    Shiboken::AutoDecRef tupleArgs(PyList_AsTuple(pyArgs));
    return PyObject_CallObject(pyMethod, tupleArgs);
}

PyObject* signalInstanceGetItem(PyObject* self, PyObject* key)
{
    PySideSignalInstance* data = reinterpret_cast<PySideSignalInstance*>(self);
    char* sigKey = PySide::Signal::parseSignature(key);
    char* sig = PySide::Signal::buildSignature(data->d->signalName, sigKey);
    free(sigKey);
    const char* sigName = data->d->signalName;

    while(data) {
        if (strcmp(data->d->signature, sig) == 0) {
            free(sig);
            PyObject *result = reinterpret_cast<PyObject*>(data);
            Py_INCREF(result);
            return result;
        }
        data = reinterpret_cast<PySideSignalInstance*>(data->d->next);
    }
    PyErr_Format(PyExc_IndexError, "Signature %s not found for signal: %s", sig, sigName);
    free(sig);

    return 0;
}

PyObject* signalInstanceDisconnect(PyObject* self, PyObject* args)
{
    PySideSignalInstance* source = reinterpret_cast<PySideSignalInstance*>(self);
    Shiboken::AutoDecRef pyArgs(PyList_New(0));

    PyObject* slot;
    if (PyTuple_Check(args) && PyTuple_GET_SIZE(args))
        slot = PyTuple_GET_ITEM(args, 0);
    else
        slot = Py_None;

    bool match = false;
    if (slot->ob_type == &PySideSignalInstanceType) {
        PySideSignalInstance *target = reinterpret_cast<PySideSignalInstance*>(slot);
        if (QMetaObject::checkConnectArgs(source->d->signature, target->d->signature)) {
            PyList_Append(pyArgs, source->d->source);
            Shiboken::AutoDecRef source_signature(PySide::Signal::buildQtCompatible(source->d->signature));
            PyList_Append(pyArgs, source_signature);

            PyList_Append(pyArgs, target->d->source);
            Shiboken::AutoDecRef target_signature(PySide::Signal::buildQtCompatible(target->d->signature));
            PyList_Append(pyArgs, target_signature);
            match = true;
        }
    } else {
        //try the first signature
        PyList_Append(pyArgs, source->d->source);
        Shiboken::AutoDecRef signature(PySide::Signal::buildQtCompatible(source->d->signature));
        PyList_Append(pyArgs, signature);

        // disconnect all, so we need to use the c++ signature disconnect(qobj, signal, 0, 0)
        if (slot == Py_None)
            PyList_Append(pyArgs, slot);
        PyList_Append(pyArgs, slot);
        match = true;
    }

    if (match) {
        Shiboken::AutoDecRef tupleArgs(PyList_AsTuple(pyArgs));
        Shiboken::AutoDecRef pyMethod(PyObject_GetAttrString(source->d->source, "disconnect"));
        return PyObject_CallObject(pyMethod, tupleArgs);
    }

    return 0;
}

PyObject* signalCall(PyObject* self, PyObject* args, PyObject* kw)
{
    PySideSignal* signal = reinterpret_cast<PySideSignal*>(self);

    if (!signal->homonymousMethod) {
        PyErr_SetString(PyExc_TypeError, "native Qt signal is not callable");
        return 0;
    }

    descrgetfunc getDescriptor = signal->homonymousMethod->ob_type->tp_descr_get;
    Shiboken::AutoDecRef homonymousMethod(getDescriptor(signal->homonymousMethod, 0, 0));

    if (PyCFunction_GET_FLAGS(homonymousMethod.object()) & METH_STATIC)
        return PyCFunction_Call(homonymousMethod, args, kw);

    ternaryfunc callFunc = signal->homonymousMethod->ob_type->tp_call;
    return callFunc(homonymousMethod, args, kw);
}

PyObject* signalInstanceCall(PyObject* self, PyObject* args, PyObject* kw)
{
    PySideSignalInstance* PySideSignal = reinterpret_cast<PySideSignalInstance*>(self);
    if (!PySideSignal->d->homonymousMethod) {
        PyErr_SetString(PyExc_TypeError, "native Qt signal is not callable");
        return 0;
    }

    descrgetfunc getDescriptor = PySideSignal->d->homonymousMethod->ob_type->tp_descr_get;
    Shiboken::AutoDecRef homonymousMethod(getDescriptor(PySideSignal->d->homonymousMethod, PySideSignal->d->source, 0));
    return PyCFunction_Call(homonymousMethod, args, kw);
}

} // extern "C"

namespace PySide { namespace Signal {

void init(PyObject* module)
{
    if (PyType_Ready(&PySideSignalType) < 0)
        return;

    Py_INCREF(&PySideSignalType);
    PyModule_AddObject(module, SIGNAL_CLASS_NAME, ((PyObject*)&PySideSignalType));

    if (PyType_Ready(&PySideSignalInstanceType) < 0)
        return;

    Py_INCREF(&PySideSignalInstanceType);
}

bool checkType(PyObject* pyObj)
{
    if (pyObj)
        return PyType_IsSubtype(pyObj->ob_type, &PySideSignalType);
    return false;
}

void updateSourceObject(PyObject* source)
{
    PyTypeObject * objType = reinterpret_cast<PyTypeObject *>(PyObject_Type(source));

    Py_ssize_t pos = 0;
    PyObject* value;
    PyObject* key;

    while (PyDict_Next(objType->tp_dict, &pos, &key, &value)) {
        if (PyObject_TypeCheck(value, &PySideSignalType)) {
            Shiboken::AutoDecRef signalInstance((PyObject*)PyObject_New(PySideSignalInstance, &PySideSignalInstanceType));
            instanceInitialize(signalInstance.cast<PySideSignalInstance*>(), key, reinterpret_cast<PySideSignal*>(value), source, 0);
            PyObject_SetAttr(source, key, signalInstance);
        }
    }

    Py_XDECREF(objType);
}

char* getTypeName(PyObject* type)
{
    if (PyType_Check(type)) {
        char *typeName = NULL;
        if (PyType_IsSubtype(reinterpret_cast<PyTypeObject*>(type), reinterpret_cast<PyTypeObject*>(&SbkObject_Type))) {
            SbkObjectType* objType = reinterpret_cast<SbkObjectType*>(type);
            typeName = strdup(Shiboken::ObjectType::getOriginalName(objType));
        } else {
            // Translate python types to Qt names
            PyTypeObject *objType = reinterpret_cast<PyTypeObject*>(type);
            if ((objType == &PyString_Type)  ||  (objType == &PyUnicode_Type))
                typeName = strdup("QString");
            else if (objType == &PyInt_Type)
                typeName = strdup("int");
            else if (objType == &PyLong_Type)
                typeName = strdup("long");
            else if (objType == &PyFloat_Type)
                typeName = strdup("double");
            else if (objType == &PyBool_Type)
                typeName = strdup("bool");
            else if (objType->ob_type == &SbkEnumType_Type) {
                typeName = strdup(Shiboken::Enum::getCppName(objType));
            } else {
                typeName = strdup("PyObject");
            }
        }
        return typeName;
    } else if (PyString_Check(type)) {
        return strdup(PyString_AS_STRING(type));
    } else if (type == Py_None) {
        return strdup("void");
    }
    return 0;
}

char* buildSignature(const char *name, const char *signature)
{
    QString signal;
    signal.sprintf("%s(%s)", name, signature);
    return strdup(QMetaObject::normalizedSignature(signal.toAscii()));
}

char* parseSignature(PyObject *args)
{
    char *signature = 0;
    if (args && (PyString_Check(args) || !PySequence_Check(args)))
        return getTypeName(args);

    for(Py_ssize_t i = 0, i_max = PySequence_Size(args); i < i_max; i++) {
        Shiboken::AutoDecRef arg(PySequence_ITEM(args, i));
        char* typeName = getTypeName(arg);
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

void appendSignature(PySideSignal* self, char* signature)
{
    self->signaturesSize++;

    if (self->signaturesSize > 1) {
        self->signatures = (char**) realloc(self->signatures, sizeof(char**) * self->signaturesSize);
    } else {
        self->signatures = (char**) malloc(sizeof(char**));
    }
    self->signatures[self->signaturesSize-1] = signature;
}

PySideSignalInstance* initialize(PySideSignal* self, PyObject* name, PyObject *object)
{
    PySideSignalInstance* instance = PyObject_New(PySideSignalInstance, &PySideSignalInstanceType);
    instanceInitialize(instance, name, self, object, 0);
    return instance;
}

void instanceInitialize(PySideSignalInstance* self, PyObject* name, PySideSignal* data, PyObject* source, int index)
{
    self->d = new PySideSignalInstancePrivate;
    PySideSignalInstancePrivate* selfPvt = self->d;
    selfPvt->next = 0;
    if (data->signalName)
        selfPvt->signalName = strdup(data->signalName);
    else {
        selfPvt->signalName = strdup(PyString_AsString(name));
        data->signalName = strdup(selfPvt->signalName);
    }

    selfPvt->source = source;
    selfPvt->signature = buildSignature(self->d->signalName, data->signatures[index]);
    selfPvt->homonymousMethod = 0;
    if (data->homonymousMethod) {
        selfPvt->homonymousMethod = data->homonymousMethod;
        Py_INCREF(selfPvt->homonymousMethod);
    }
    index++;

    if (index < data->signaturesSize) {
        selfPvt->next = PyObject_New(PySideSignalInstance, &PySideSignalInstanceType);
        instanceInitialize(selfPvt->next, name, data, source, index);
    }
}

bool connect(PyObject* source, const char* signal, PyObject* callback)
{
    Shiboken::AutoDecRef pyMethod(PyObject_GetAttrString(source, "connect"));
    if (pyMethod.isNull())
        return false;

    Shiboken::AutoDecRef pySignature(PyString_FromString(signal));
    Shiboken::AutoDecRef pyArgs(PyTuple_Pack(3, source, pySignature.object(), callback));
    return PyObject_CallObject(pyMethod, pyArgs);
}

PySideSignalInstance* newObjectFromMethod(PyObject* source, const QList<QMetaMethod>& methodList)
{
    PySideSignalInstance *root = 0;
    PySideSignalInstance *previous = 0;
    foreach(QMetaMethod m, methodList) {
        PySideSignalInstance *item = PyObject_New(PySideSignalInstance, &PySideSignalInstanceType);
        if (!root)
            root = item;

        if (previous)
            previous->d->next = item;

        item->d = new PySideSignalInstancePrivate;
        PySideSignalInstancePrivate* selfPvt = item->d;
        selfPvt->source = source;
        QByteArray cppName(m.signature());
        cppName = cppName.mid(0, cppName.indexOf('('));
        // separe SignalName
        selfPvt->signalName = strdup(cppName.data());
        selfPvt->signature = strdup(m.signature());
        selfPvt->homonymousMethod = 0;
        selfPvt->next = 0;
    }
    return root;
}

PySideSignal* newObject(const char* name, ...)
{
    va_list listSignatures;
    char* sig = 0;
    PySideSignal* self = PyObject_New(PySideSignal, &PySideSignalType);
    self->signalName = strdup(name);
    self->signaturesSize = 0;
    self->signatures = 0;
    self->initialized = 0;
    self->homonymousMethod = 0;

    va_start(listSignatures, name);
    sig = va_arg(listSignatures, char*);

    while(sig != NULL) {
        appendSignature(self, strdup(sig));
        sig = va_arg(listSignatures, char*);
    }

    va_end(listSignatures);

    return self;
}


PyObject* buildQtCompatible(const char* signature)
{
    QByteArray ba;
    ba.append(QT_SIGNAL_SENTINEL);
    ba.append(signature);
    return PyString_FromStringAndSize(ba, ba.size());
}

void addSignalToWrapper(SbkObjectType* wrapperType, const char* signalName, PySideSignal* signal)
{
    PyObject* typeDict = wrapperType->super.ht_type.tp_dict;
    PyObject* homonymousMethod;
    if ((homonymousMethod = PyDict_GetItemString(typeDict, signalName))) {
        Py_INCREF(homonymousMethod);
        signal->homonymousMethod = homonymousMethod;
    }
    PyDict_SetItemString(typeDict, signalName, reinterpret_cast<PyObject*>(signal));
}

PyObject* getObject(PySideSignalInstance* signal)
{
    return signal->d->source;
}

const char* getSignature(PySideSignalInstance* signal)
{
    return signal->d->signature;
}


const char** getSignatures(PyObject* signal, int *size)
{
    PySideSignal *self = reinterpret_cast<PySideSignal*>(signal);
    *size = self->signaturesSize;
    return (const char**) self->signatures;
}

QStringList getArgsFromSignature(const char* signature, bool* isShortCircuit)
{
    QString qsignature(signature);
    QStringList result;
    QRegExp splitRegex("\\s*,\\s*");

    if (isShortCircuit)
        *isShortCircuit = !qsignature.contains('(');
    if (qsignature.contains("()") || qsignature.contains("(void)")) {
        return result;
    } else if (qsignature.contains('(')) {
        static QRegExp regex(".+\\((.*)\\)");
        //get args types
        QString types = qsignature.replace(regex, "\\1");
        result = types.split(splitRegex);
    }
    return result;
}

QString getCallbackSignature(const char* signal, QObject* receiver, PyObject* callback, bool encodeName)
{
    QByteArray functionName;
    QByteArray signature;
    QStringList args;
    int numArgs = -1;
    bool useSelf = false;
    bool isMethod = PyMethod_Check(callback);
    bool isFunction = PyFunction_Check(callback);

    if (isMethod || isFunction) {
        PyObject* function = isMethod ? PyMethod_GET_FUNCTION(callback) : callback;
        PyCodeObject* objCode = reinterpret_cast<PyCodeObject*>(PyFunction_GET_CODE(function));
        functionName = PyString_AS_STRING(reinterpret_cast<PyFunctionObject*>(function)->func_name);
        useSelf = isMethod;
        numArgs = objCode->co_flags & CO_VARARGS ? -1 : objCode->co_argcount;
    } else if (PyCFunction_Check(callback)) {
        functionName = ((PyCFunctionObject*)callback)->m_ml->ml_name;
        useSelf = ((PyCFunctionObject*)callback)->m_self;
        int flags = ((PyCFunctionObject*)callback)->m_ml->ml_flags;

        if (receiver) {
            //Search for signature on metaobject
            const QMetaObject *mo = receiver->metaObject();
            QByteArray prefix(functionName);
            prefix += '(';
            for(int i=0; i < mo->methodCount(); i++) {
                QMetaMethod me = mo->method(i);
                if ((strncmp(me.signature(), prefix, prefix.size()) == 0) &&
                    QMetaObject::checkConnectArgs(signal, me.signature())) {
                    numArgs = me.parameterTypes().size() + useSelf;
                    break;
                }
           }
        }

        if (numArgs == -1) {
            if (flags & METH_VARARGS)
                numArgs = -1;
            else if (flags & METH_NOARGS)
                numArgs = 0;
        }
    } else if (PyCallable_Check(callback)) {
        functionName = "__callback"+QByteArray::number((qlonglong)callback);
    }

    Q_ASSERT(!functionName.isEmpty());

    bool isShortCircuit = false;

    if (encodeName)
        signature = qPrintable(codeCallbackName(callback, functionName));
    else
        signature = functionName;

    args = getArgsFromSignature(signal, &isShortCircuit);

    if (!isShortCircuit) {
        signature.append('(');
        if (numArgs == -1)
            numArgs = std::numeric_limits<int>::max();
        while (args.count() && (args.count() > (numArgs - useSelf))) {
            args.removeLast();
        }
        signature.append(args.join(","));
        signature.append(')');
    }
    return signature;
}

bool isQtSignal(const char* signal)
{
    return (signal && signal[0] == QT_SIGNAL_SENTINEL);
}

bool checkQtSignal(const char* signal)
{
    if (!isQtSignal(signal)) {
        PyErr_SetString(PyExc_TypeError, "Use the function PySide.QtCore.SIGNAL on signals");
        return false;
    }
    return true;
}

QString  codeCallbackName(PyObject* callback, const QString& funcName)
{
    if (PyMethod_Check(callback)) {
        PyObject *self = PyMethod_GET_SELF(callback);
        PyObject *func = PyMethod_GET_FUNCTION(callback);
        return funcName + QString::number(quint64(self), 16) + QString::number(quint64(func), 16);
    } else
        return funcName + QString::number(quint64(callback), 16);
}

} //namespace Signal
} //namespace PySide


#define protected public

#include <shiboken.h>
#include <Python.h>
#include <QDebug>

#include "qsignal.h"
#include "signalmanager.h"

#define SIGNAL_CLASS_NAME "Signal"

namespace PySide
{

extern "C"
{

static int qsignal_init(PyObject*, PyObject*, PyObject*);
static void qsignal_free(void*);
static void qsignal_instance_free(void*);

//methods
static PyObject* qsignal_instance_connect(PyObject *self, PyObject *args, PyObject *kw);
static PyObject* qsignal_instance_disconnect(PyObject *self, PyObject *args);
static PyObject* qsignal_instance_emit(PyObject *self, PyObject *args);
static PyObject* qsignal_instance_get_item(PyObject *self, PyObject *key);

//aux
static char* qsignal_build_signature(const char *name, const char *signature);
static const char* qsignal_get_type_name(PyObject *type);
static void qsignal_append_signature(SignalData *self, PyObject *args);
static void qsignal_instance_initialize(PyObject *instance, PyObject *name, SignalData *data, PyObject *source, int index);
static char* qsignal_parse_signature(PyObject *args);

PyTypeObject PySideSignal_Type = {
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
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,        /*tp_flags*/
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
    (initproc)qsignal_init,    /*tp_init */
    0,                         /*tp_alloc */
    PyType_GenericNew,         /*tp_new */
    qsignal_free,              /*tp_free */
    0,                         /*tp_is_gc */
    0,                         /*tp_bases */
    0,                         /*tp_mro */
    0,                         /*tp_cache */
    0,                         /*tp_subclasses */
    0,                         /*tp_weaklist */
    0,                         /*tp_del */
};

static PyMethodDef PySideQtSignalInstance_methods[] = {
    {"connect", (PyCFunction)qsignal_instance_connect, METH_VARARGS|METH_KEYWORDS},
    {"disconnect", (PyCFunction)qsignal_instance_disconnect, METH_VARARGS},
    {"emit", (PyCFunction)qsignal_instance_emit, METH_VARARGS},
    {NULL}  /* Sentinel */
};

static PyMappingMethods PySideQSignalInstance_as_mapping = {
    0,
    qsignal_instance_get_item,
    0
};

PyTypeObject PySideSignalInstance_Type = {
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
    &PySideQSignalInstance_as_mapping,  /*tp_as_mapping*/
    0,                         /*tp_hash */
    0,                         /*tp_call*/
    0,                         /*tp_str*/
    0,                         /*tp_getattro*/
    0,                         /*tp_setattro*/
    0,                         /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /*tp_flags*/
    SIGNAL_CLASS_NAME,         /*tp_doc */
    0,                         /*tp_traverse */
    0,                         /*tp_clear */
    0,                         /*tp_richcompare */
    0,                         /*tp_weaklistoffset */
    0,                         /*tp_iter */
    0,                         /*tp_iternext */
    PySideQtSignalInstance_methods, /*tp_methods */
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
    qsignal_instance_free,     /*tp_free */
    0,                         /*tp_is_gc */
    0,                         /*tp_bases */
    0,                         /*tp_mro */
    0,                         /*tp_cache */
    0,                         /*tp_subclasses */
    0,                         /*tp_weaklist */
    0,                         /*tp_del */
};


PyAPI_FUNC(void) init_signal(PyObject* module)
{
    if (PyType_Ready(&PySideSignal_Type) < 0)
        return;

    Py_INCREF(&PySideSignal_Type);
    PyModule_AddObject(module, SIGNAL_CLASS_NAME, ((PyObject*)&PySideSignal_Type));

    if (PyType_Ready(&PySideSignalInstance_Type) < 0)
        return;

    Py_INCREF(&PySideSignalInstance_Type);
}


} // extern "C"


PyObject* qsignal_instance_get_item(PyObject *self, PyObject *key)
{
    SignalInstanceData *data = reinterpret_cast<SignalInstanceData*>(self);
    char *sig_key = qsignal_parse_signature(key);
    char *sig = qsignal_build_signature(data->signal_name, sig_key);
    free(sig_key);

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

void signal_update_source(PyObject *source)
{
    PyObject *key, *value;
    Py_ssize_t pos = 0;
    PyTypeObject *obType = source->ob_type;

    while (PyDict_Next(obType->tp_dict, &pos, &key, &value)) {
        if (value->ob_type == &PySideSignal_Type) {
            PyObject *signal_instance = (PyObject*)PyObject_New(SignalData, &PySideSignalInstance_Type);
            qsignal_instance_initialize(signal_instance, key, reinterpret_cast<SignalData*>(value), source, 0);
            PyObject_SetAttr(source, key, signal_instance);
            Py_DECREF(signal_instance);
        }
    }
}

const char* qsignal_get_type_name(PyObject *type)
{
    if (PyType_Check(type)) {
        //tp_name return the full name
        Shiboken::AutoDecRef type_name(PyObject_GetAttrString(type, "__name__"));
        return PyString_AS_STRING((PyObject*)type_name);
    } else if (PyString_Check(type)) {
        return PyString_AS_STRING(type);
    }
    return "";
}

char* qsignal_build_signature(const char *name, const char *signature)
{
    QString signal;
    return strdup(QMetaObject::normalizedSignature(signal.toAscii()));
}

char* qsignal_parse_signature(PyObject *args)
{
    char *signature = 0;

    if (args && !PySequence_Check(args) && (args != Py_None && args))
        return strdup(qsignal_get_type_name(args));

    for(Py_ssize_t i=0, i_max=PySequence_Size(args); i < i_max; i++) {
        Shiboken::AutoDecRef arg(PySequence_ITEM(args, i));
        const char *type_name = qsignal_get_type_name(arg);
        if (strlen(type_name) > 0) {
            if (signature) {
                signature = strcat(signature, ",");
                signature = strcat(signature, type_name);
            } else {
                signature = strdup(type_name);
            }
        }
    }

    return signature;
}

void qsignal_append_signature(SignalData *self, PyObject *args)
{
    char *signature = qsignal_parse_signature(args);

    self->signatures_size++;

    if (self->signatures_size > 1) {
        self->signatures = (char**) realloc(self->signatures, sizeof(char**) * self->signatures_size);
    } else {
        self->signatures = (char**) malloc(sizeof(char**));
    }
    self->signatures[self->signatures_size-1] = signature;
}

int qsignal_init(PyObject *self, PyObject *args, PyObject *kwds)
{
    static PyObject *emptyTuple = 0;
    static const char *kwlist[] = {"name", 0};
    char* arg_name = 0;

    if (emptyTuple == 0)
        emptyTuple = PyTuple_New(0);

    if (!PyArg_ParseTupleAndKeywords(emptyTuple, kwds,
                                     "|s:QtCore."SIGNAL_CLASS_NAME, (char**) kwlist, &arg_name))
        return 0;

    bool tupled_args = false;
    SignalData *data = reinterpret_cast<SignalData*>(self);
    if (arg_name) {
        data->signal_name = strdup(arg_name);
    }

    for(Py_ssize_t i=0, i_max=PyTuple_Size(args); i < i_max; i++) {
        PyObject *arg = PyTuple_GET_ITEM(args, i);
        if (PySequence_Check(arg)) {
            tupled_args = true;
            qsignal_append_signature(data, arg);
        }
    }

    if (!tupled_args)
        qsignal_append_signature(data, args);


    return 1;
}

void qsignal_free(void *self)
{
    PyObject *pySelf = reinterpret_cast<PyObject*>(self);
    SignalData *data = reinterpret_cast<SignalData*>(self);

    for(int i=0, i_max=data->signatures_size; i < i_max; i++) {
        if (data->signatures[i])
            free(data->signatures[i]);
    }

    free(data->signatures);
    free(data->signal_name);
    data->initialized = false;
    data->signatures_size = 0;

    pySelf->ob_type->tp_base->tp_free(self);
}

void qsignal_instance_free(void *self)
{
    PyObject *pySelf = reinterpret_cast<PyObject*>(self);
    SignalInstanceData *data = reinterpret_cast<SignalInstanceData*>(self);

    free(data->signal_name);
    free(data->signature);

    while(data) {
        Py_XDECREF(data->next);
        data = reinterpret_cast<SignalInstanceData*>(data->next);
    }
    pySelf->ob_type->tp_base->tp_free(self);
}

void qsignal_instance_initialize(PyObject *instance, PyObject *name, SignalData *data, PyObject *source, int index)
{
    if (data->initialized)
        return;

    SignalInstanceData *self = reinterpret_cast<SignalInstanceData*>(instance);
    if (data->signal_name)
        self->signal_name = strdup(data->signal_name);
    else
        self->signal_name = strdup(PyString_AsString(name));

    self->source = source;
    self->signature = qsignal_build_signature(self->signal_name, data->signatures[index]);
    index++;

    if (index < data->signatures_size) {
        self->next = (PyObject*)PyObject_New(SignalData, &PySideSignalInstance_Type);
        qsignal_instance_initialize(self->next, name, data, source, index);
    }

    if (index == 0)
        data->initialized = true;
}

PyObject* qsignal_instance_connect(PyObject *self, PyObject *args, PyObject *kwds)
{
    PyObject *slot;
    PyObject *type;
    static const char *kwlist[] = {"type", 0};

    if (!PyArg_ParseTupleAndKeywords(args, kwds,
                                     "O|O:"SIGNAL_CLASS_NAME, (char**) kwlist, &slot, &type))
        return 0;

    SignalInstanceData *source = reinterpret_cast<SignalInstanceData*>(self);
    Shiboken::AutoDecRef pyArgs(PyList_New(0));

    bool match = false;
    if (slot->ob_type == &PySideSignalInstance_Type) {
        //TODO: find best match
        SignalInstanceData *target = reinterpret_cast<SignalInstanceData*>(slot);

        if (QMetaObject::checkConnectArgs(source->signature, target->signature)) {
            PyList_Append(pyArgs, source->source);
            Shiboken::AutoDecRef source_signature(PyString_FromString(source->signature));
            PyList_Append(pyArgs, source_signature);

            PyList_Append(pyArgs, target->source);
            Shiboken::AutoDecRef target_signature(PyString_FromString(target->signature));
            PyList_Append(pyArgs, target_signature);
            match = true;
        }
    } else {
        //try the first signature
        PyList_Append(pyArgs, source->source);
        Shiboken::AutoDecRef signature(PyString_FromString(source->signature));
        PyList_Append(pyArgs, signature);

        PyList_Append(pyArgs, slot);
        match = true;
    }

    if (match) {
        Shiboken::AutoDecRef tupleArgs(PyList_AsTuple(pyArgs));
        Shiboken::AutoDecRef pyMethod(PyObject_GetAttrString(source->source, "connect"));
        return  PyObject_CallObject(pyMethod, tupleArgs);
    }

    return 0;
}

PyObject* qsignal_instance_disconnect(PyObject *self, PyObject *args)
{
    SignalInstanceData *source = reinterpret_cast<SignalInstanceData*>(self);
    Shiboken::AutoDecRef pyArgs(PyList_New(0));

    PyObject *slot;
    if PyTuple_Check(args)
        slot = PyTuple_GET_ITEM(args, 0);
    else
        slot = args;

    bool match = false;
    if (slot->ob_type == &PySideSignalInstance_Type) {
        SignalInstanceData *target = reinterpret_cast<SignalInstanceData*>(slot);
        if (QMetaObject::checkConnectArgs(source->signature, target->signature)) {
            PyList_Append(pyArgs, source->source);
            Shiboken::AutoDecRef source_signature(PyString_FromString(source->signature));
            PyList_Append(pyArgs, source_signature);

            PyList_Append(pyArgs, target->source);
            Shiboken::AutoDecRef target_signature(PyString_FromString(target->signature));
            PyList_Append(pyArgs, target_signature);
            match = true;
        }
    } else {
        //try the first signature
        PyList_Append(pyArgs, source->source);
        Shiboken::AutoDecRef signature(PyString_FromString(source->signature));
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

PyObject* qsignal_instance_emit(PyObject *self, PyObject *args)
{
    SignalInstanceData *source = reinterpret_cast<SignalInstanceData*>(self);

    Shiboken::AutoDecRef pyArgs(PyList_New(0));
    Shiboken::AutoDecRef source_signature(PyString_FromString(source->signature));

    PyList_Append(pyArgs, source_signature);
    for(Py_ssize_t i=0, i_max=PyTuple_Size(args); i < i_max; i++)
        PyList_Append(pyArgs, PyTuple_GetItem(args, i));

    Shiboken::AutoDecRef pyMethod(PyObject_GetAttrString(source->source, "emit"));

    Shiboken::AutoDecRef tupleArgs(PyList_AsTuple(pyArgs));
    return PyObject_CallObject(pyMethod, tupleArgs);
}

} //namespace PySide

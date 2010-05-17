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


PyAPI_FUNC(void) init_signal(PyObject* module)
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

void signal_update_source(PyObject* source)
{
    PyObject* key;
    PyObject* value;
    Py_ssize_t pos = 0;
    PyTypeObject* obType = source->ob_type;

    while (PyDict_Next(obType->tp_dict, &pos, &key, &value)) {
        if (value->ob_type == &Signal_Type) {
            Shiboken::AutoDecRef signalInstance(reinterpret_cast<PyObject*>(PyObject_New(SignalInstanceData, &SignalInstance_Type)));
            signal_instance_initialize(signalInstance, key, reinterpret_cast<SignalData*>(value), source, 0);
            PyObject_SetAttr(source, key, signalInstance);
        }
    }
}

char* signal_get_type_name(PyObject* type)
{
    if (PyType_Check(type)) {
        //tp_name return the full name
        Shiboken::AutoDecRef typeName(PyObject_GetAttrString(type, "__name__"));
        return strdup(PyString_AS_STRING(typeName.object()));
    } else if (PyString_Check(type)) {
        return strdup(PyString_AS_STRING(type));
    }
    return 0;
}

char* signal_build_signature(const char *name, const char *signature)
{
    QString signal;
    signal.sprintf("2%s(%s)", name, signature);
    return strdup(QMetaObject::normalizedSignature(signal.toAscii()));
}

char* signal_parse_signature(PyObject *args)
{
    char *signature = 0;

    if (args && !PySequence_Check(args) && (args != Py_None && args))
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
        if (PySequence_Check(arg)) {
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
    data->initialized = false;
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
    if (data->initialized)
        return;

    SignalInstanceData *self = reinterpret_cast<SignalInstanceData*>(instance);
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

    if (index == 0)
        data->initialized = true;
}

PyObject* signal_instance_connect(PyObject* self, PyObject* args, PyObject* kwds)
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
    if (slot->ob_type == &SignalInstance_Type) {
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

PyObject* signal_instance_emit(PyObject* self, PyObject* args)
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

PyObject* signal_new(const char* name, ...)
{
    va_list listSignatures;
    char* sig;
    SignalData* self = PyObject_New(SignalData, &Signal_Type);

    va_start(listSignatures, name);
    sig = va_arg(listSignatures, char*);

    while(sig != NULL) {
        signal_append_signature(self, strdup(sig));
        sig = va_arg(listSignatures, char*);
    }

    va_end(listSignatures);

    return reinterpret_cast<PyObject*>(self);
}


} //namespace PySide

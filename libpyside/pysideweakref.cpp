#include "pysideweakref.h"

#include <Python.h>

typedef struct {
    PyObject_HEAD
    /* Type-specific fields go here. */
    PySideWeakRefFunction weakref_func;
    void*  user_data;
} PySideCallableObject;

static PyObject* CallableObject_call(PyObject* callable_object, PyObject* args, PyObject* kw);

static PyTypeObject PySideCallableObjectType = {
    PyVarObject_HEAD_INIT(0, 0)
    const_cast<char*>("PySide.Callable"),
    sizeof(PySideCallableObject),    /*tp_basicsize*/
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
    CallableObject_call,       /*tp_call*/
    0,                         /*tp_str*/
    0,                         /*tp_getattro*/
    0,                         /*tp_setattro*/
    0,                         /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT,        /*tp_flags*/
    0,                         /* tp_doc */
};

static PyObject* CallableObject_call(PyObject* callable_object, PyObject* args, PyObject* kw)
{
    PySideCallableObject* obj = (PySideCallableObject*)(callable_object);
    obj->weakref_func(obj->user_data);

    Py_XDECREF(PyTuple_GET_ITEM(args, 0)); //kill weak ref object
    Py_RETURN_NONE;
}

namespace PySide { namespace WeakRef {

PyObject* create(PyObject* obj, PySideWeakRefFunction func, void* userData)
{
    if (obj == Py_None)
        return 0;

    if (Py_TYPE(&PySideCallableObjectType) == 0)
    {
        Py_TYPE(&PySideCallableObjectType) = &PyType_Type;
        PyType_Ready(&PySideCallableObjectType);
    }

    PySideCallableObject* callable = PyObject_New(PySideCallableObject, &PySideCallableObjectType);
    if (!callable || PyErr_Occurred())
        return 0;

    PyObject* weak = PyWeakref_NewRef(obj, (PyObject*)callable);
    if (!weak || PyErr_Occurred())
        return 0;

    Py_DECREF(callable);

    callable->weakref_func = func;
    callable->user_data = userData;
    return (PyObject*)weak;
}

} }  //namespace


#include <signalmanager.h>
#include <dynamicqmetaobject.h>

#define SLOT_DEC_NAME "Slot"
typedef struct
{
    PyObject_HEAD
    char* slot_name;
    char* args;
    char* result_type;
} SlotData;

extern "C"
{

static int qslot_init(PyObject *self, PyObject *arg, PyObject *kw);
static PyObject* qslot_call(PyObject *self, PyObject *arg, PyObject *kw);

// Class Definition -----------------------------------------------
static PyTypeObject PySideSlot_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "QtCore."SLOT_DEC_NAME,    /*tp_name*/
    sizeof(SlotData),          /*tp_basicsize*/
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
    qslot_call,                /*tp_call*/
    0,                         /*tp_str*/
    0,                         /*tp_getattro*/
    0,                         /*tp_setattro*/
    0,                         /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,        /*tp_flags*/
    SLOT_DEC_NAME,             /*tp_doc */
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
    (initproc)qslot_init,      /*tp_init */
    0,                         /*tp_alloc */
    PyType_GenericNew,         /*tp_new */
    0,                         /*tp_free */
    0,                         /*tp_is_gc */
    0,                         /*tp_bases */
    0,                         /*tp_mro */
    0,                         /*tp_cache */
    0,                         /*tp_subclasses */
    0,                         /*tp_weaklist */
    0,                         /*tp_del */
};

static PyMethodDef PySideQtSlot_methods[] = {
    {NULL}  /* Sentinel */
};

PyAPI_FUNC(void) init_slot(PyObject* module)
{
    if (PyType_Ready(&PySideSlot_Type) < 0)
        return;

    Py_INCREF(&PySideSlot_Type);
    PyModule_AddObject(module, SLOT_DEC_NAME, ((PyObject*)&PySideSlot_Type));
}


} // extern "C"

static const char* qslot_get_type_name(PyObject *type)
{
    if (PyType_Check(type)) {
        PyTypeObject *obj_type = (PyTypeObject*)(type);
        //tp_name return the full name
        Shiboken::AutoDecRef type_name(PyObject_GetAttrString(type, "__name__"));
        return PyString_AS_STRING((PyObject*)type_name);
    } else if (PyString_Check(type)) {
        return PyString_AS_STRING(type);
    }
    return "";
}

static int qslot_init(PyObject *self, PyObject *args, PyObject *kw)
{
    static PyObject *emptyTuple = 0;
    static const char *kwlist[] = {"name", "result", 0};
    char* arg_name = 0;
    PyObject* arg_result = 0;

    if (emptyTuple == 0)
        emptyTuple = PyTuple_New(0);

    if (!PyArg_ParseTupleAndKeywords(emptyTuple, kw, "|sN:QtCore."SLOT_DEC_NAME, (char**) kwlist, &arg_name, &arg_result))
        return 0;

    SlotData *data = reinterpret_cast<SlotData*>(self);
    for(Py_ssize_t i=0, i_max=PyTuple_Size(args); i < i_max; i++) {
        PyObject *arg_type = PyTuple_GET_ITEM(args, i);
        const char *type_name = qslot_get_type_name(arg_type);
        if (strlen(type_name) > 0) {
            if (data->args) {
                data->args = strcat(data->args, ",");
                data->args = strcat(data->args, type_name);
            } else {
                data->args = strdup(type_name);
            }
        }
    }

    if (arg_name)
        data->slot_name = strdup(arg_name);

    if (arg_result)
        data->result_type = strdup(qslot_get_type_name(arg_result));

    return 1;
}

static PyObject* qslot_call(PyObject *self, PyObject *args, PyObject *kw)
{
    PyObject *callback;
    callback = PyTuple_GetItem(args, 0);
    Py_INCREF(callback);

    if (PyFunction_Check(callback)) {
        SlotData *data = reinterpret_cast<SlotData*>(self);

        if (!data->slot_name) {
            PyObject *func_name = ((PyFunctionObject*)callback)->func_name;
            data->slot_name = strdup(PyString_AS_STRING(func_name));
        }

        QString signature;
        signature.sprintf("%s(%s)",data->slot_name, data->args);

        PyObject *pySignature = PyString_FromString(QMetaObject::normalizedSignature(signature.toAscii()));
        PyObject *signature_list = 0;
        if (PyObject_HasAttrString(callback, PYSIDE_SLOT_LIST_ATTR)) {
            signature_list = PyObject_GetAttrString(callback, PYSIDE_SLOT_LIST_ATTR);
        } else {
            signature_list = PyList_New(0);
            PyObject_SetAttrString(callback, PYSIDE_SLOT_LIST_ATTR, signature_list);
            Py_DECREF(signature_list);
        }

        PyList_Append(signature_list, pySignature);
        Py_DECREF(pySignature);

        //clear data
        free(data->slot_name);
        data->slot_name = 0;
        free(data->result_type);
        data->result_type = 0;
        free(data->args);
        data->args = 0;
        return callback;
    }
    return callback;
}


// Borrowed reference to QtGui module
extern PyObject* moduleQtGui;

static int QApplicationArgCount;
static char** QApplicationArgValues;
static const char QAPP_MACRO[] = "qApp";

void QApplication_constructor(PyObject* self, PyObject* args, QApplicationWrapper** cptr)
{
    if (QApplication::instance()) {
        PyErr_SetString(PyExc_RuntimeError, "A QApplication instance already exists.");
        return;
    }

    int numArgs = PyTuple_GET_SIZE(args);
    if (numArgs != 1
        || !Shiboken::sequenceToArgcArgv(PyTuple_GET_ITEM(args, 0), &QApplicationArgCount, &QApplicationArgValues, "PySideApp")) {
        PyErr_BadArgument();
        return;
    }

    *cptr = new QApplicationWrapper(QApplicationArgCount, QApplicationArgValues);
    Shiboken::Object::releaseOwnership(reinterpret_cast<SbkObject*>(self));

    // Verify if qApp is in main module
    PyObject* globalsDict = PyEval_GetGlobals();
    if (globalsDict) {
        PyObject* qAppObj = PyDict_GetItemString(globalsDict, QAPP_MACRO);
        if (qAppObj)
            PyDict_SetItemString(globalsDict, QAPP_MACRO, self);
    }

    PyObject_SetAttrString(moduleQtGui, QAPP_MACRO, self);
    PySide::registerCleanupFunction(&PySide::destroyQCoreApplication);
    Py_INCREF(self);
}

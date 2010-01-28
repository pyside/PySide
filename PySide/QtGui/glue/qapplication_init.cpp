// Borrowed reference to QtGui module
extern PyObject* moduleQtGui;
// Global variables used to store argc and argv values, defined in QtCore binding
extern int QCoreApplicationArgCount;
extern char** QCoreApplicationArgValues;
extern void DeleteQCoreApplicationAtExit();

int SbkQApplication_Init(PyObject* self, PyObject* args, PyObject*)
{
    if (QApplication::instance()) {
        PyErr_SetString(PyExc_RuntimeError, "A QApplication instance already exists.");
        return -1;
    }

    int numArgs = PyTuple_GET_SIZE(args);
    if (numArgs != 1) {
        PyErr_BadArgument();
        return -1;
    }

    if (!PySequenceToArgcArgv(PyTuple_GET_ITEM(args, 0), &QCoreApplicationArgCount, &QCoreApplicationArgValues, "PySideApp")) {
        PyErr_BadArgument();
        return -1;
    }

    SbkBaseWrapper_setCptr(self, new QApplication(QCoreApplicationArgCount, QCoreApplicationArgValues));
    SbkBaseWrapper_setValidCppObject(self, 1);
    Shiboken::BindingManager::instance().registerWrapper(reinterpret_cast<SbkBaseWrapper*>(self));

    // Verify if qApp is in main module
    const char QAPP_MACRO[] = "qApp";
    PyObject* localsDict = PyEval_GetLocals();
    if (localsDict) {
        PyObject* qAppObj = PyDict_GetItemString(localsDict, QAPP_MACRO);
        if (qAppObj)
            PyDict_SetItemString(localsDict, QAPP_MACRO, self);
    }
    PyObject_SetAttrString(moduleQtGui, QAPP_MACRO, self);

    Py_INCREF(self);
    Py_AtExit(DeleteQCoreApplicationAtExit);

    return 1;
}

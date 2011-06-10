// Borrowed reference to QtGui module
extern PyObject* moduleQtGui;

static int QApplicationArgCount;
static char** QApplicationArgValues;
static const char QAPP_MACRO[] = "qApp";

bool QApplicationConstructorStart(PyObject* argv)
{
    if (QApplication::instance()) {
        PyErr_SetString(PyExc_RuntimeError, "A QApplication instance already exists.");
        return false;
    }

    return Shiboken::sequenceToArgcArgv(argv, &QApplicationArgCount, &QApplicationArgValues, "PySideApp");
}

void QApplicationConstructorEnd(PyObject* self)
{
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

static void QApplicationConstructor(PyObject* self, PyObject* argv, QApplicationWrapper** cptr)
{
    if (QApplicationConstructorStart(argv)) {
        *cptr = new QApplicationWrapper(QApplicationArgCount, QApplicationArgValues);
        Shiboken::Object::releaseOwnership(reinterpret_cast<SbkObject*>(self));
        QApplicationConstructorEnd(self);
    }
}

template <typename T>
static void QApplicationConstructor(PyObject* self, PyObject* argv, T extraArg, QApplicationWrapper** cptr)
{
    if (QApplicationConstructorStart(argv)) {
        *cptr = new QApplicationWrapper(QApplicationArgCount, QApplicationArgValues, extraArg);
        Shiboken::Object::releaseOwnership(reinterpret_cast<SbkObject*>(self));
        QApplicationConstructorEnd(self);
    }
}

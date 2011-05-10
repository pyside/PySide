// Global variables used to store argc and argv values
static int QCoreApplicationArgCount;
static char** QCoreApplicationArgValues;

void QCoreApplication_constructor(PyObject* self, PyObject* args, QCoreApplicationWrapper** cptr)
{
    if (QCoreApplication::instance()) {
        PyErr_SetString(PyExc_RuntimeError, "A QCoreApplication instance already exists.");
        return;
    }

    int numArgs = PyTuple_GET_SIZE(args);
    if (numArgs != 1
        || !Shiboken::sequenceToArgcArgv(PyTuple_GET_ITEM(args, 0), &QCoreApplicationArgCount, &QCoreApplicationArgValues, "PySideApp")) {
        PyErr_BadArgument();
        return;
    }

    *cptr = new QCoreApplicationWrapper(QCoreApplicationArgCount, QCoreApplicationArgValues);

    Shiboken::Object::releaseOwnership(reinterpret_cast<SbkObject*>(self));
    PySide::registerCleanupFunction(&PySide::destroyQCoreApplication);
    Py_INCREF(self);
}

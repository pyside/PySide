// Global variables used to store argc and argv values
static int QCoreApplicationArgCount;
static char** QCoreApplicationArgValues;

/**
 * Called at QtCore module exit
 */
void DeleteQCoreApplicationAtExit() {
    if (QCoreApplication::instance()) {
        delete QCoreApplication::instance();
        for (int i = 0; i < QCoreApplicationArgCount; ++i)
            delete[] QCoreApplicationArgValues[i];
    }
}

int SbkQCoreApplication_Init(PyObject* self, PyObject* args, PyObject*)
{
    if (QCoreApplication::instance()) {
        PyErr_SetString(PyExc_RuntimeError, "A QCoreApplication instance already exists.");
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

    void* cptr = new QCoreApplication(QCoreApplicationArgCount, QCoreApplicationArgValues);
    Shiboken::setCppPointer(reinterpret_cast<SbkBaseWrapper*>(self),
                            Shiboken::SbkType<QCoreApplication>(),
                            cptr);
    SbkBaseWrapper_setValidCppObject(self, 1);
    Shiboken::BindingManager::instance().registerWrapper(reinterpret_cast<SbkBaseWrapper*>(self), cptr);

    Py_INCREF(self);
    Py_AtExit(DeleteQCoreApplicationAtExit);
    return 1;
}

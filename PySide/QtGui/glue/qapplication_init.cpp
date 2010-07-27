// Borrowed reference to QtGui module
extern PyObject* moduleQtGui;

static int QApplicationArgCount;
static char** QApplicationArgValues;

void DeleteQApplicationAtExit() {
    if (QApplication::instance()) {
        //disconnect and decref all widgets used on signals before destroy qApp
        PySide::SignalManager::instance().clear();
        BindingManager::instance().invalidateWrapper(QApplication::instance());
        QApplication::instance()->deleteLater();
        for (int i = 0; i < QApplicationArgCount; ++i)
            delete[] QApplicationArgValues[i];
    }
}

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

    if (!PySequenceToArgcArgv(PyTuple_GET_ITEM(args, 0), &QApplicationArgCount, &QApplicationArgValues, "PySideApp")) {
        PyErr_BadArgument();
        return -1;
    }

    void* cptr = new QApplication(QApplicationArgCount, QApplicationArgValues);
    Shiboken::setCppPointer(reinterpret_cast<SbkBaseWrapper*>(self),
                            Shiboken::SbkType<QApplication>(),
                            cptr);
    SbkBaseWrapper_setValidCppObject(self, 1);
    Shiboken::BindingManager::instance().registerWrapper(reinterpret_cast<SbkBaseWrapper*>(self), cptr);

    // Verify if qApp is in main module
    const char QAPP_MACRO[] = "qApp";
    PyObject* globalsDict = PyEval_GetGlobals();
    if (globalsDict) {
        PyObject* qAppObj = PyDict_GetItemString(globalsDict, QAPP_MACRO);
        if (qAppObj)
            PyDict_SetItemString(globalsDict, QAPP_MACRO, self);
    }
    PyObject_SetAttrString(moduleQtGui, QAPP_MACRO, self);

    Py_INCREF(self);
    Py_AtExit(DeleteQApplicationAtExit);

    return 1;
}

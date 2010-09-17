// Global variables used to store argc and argv values
static int QCoreApplicationArgCount;
static char** QCoreApplicationArgValues;

/**
 * Called at QtCore module exit
 */
void DeleteQCoreApplicationAtExit()
{
    QCoreApplication *cpp = QCoreApplication::instance();
    if (cpp) {
        Shiboken::BindingManager &bmngr = Shiboken::BindingManager::instance();
        PyObject* pySelf = bmngr.retrieveWrapper(cpp);
        cpp->flush();
        QCoreApplication::processEvents();
        bmngr.invalidateWrapper(pySelf);
        delete cpp;
    }
}

int SbkQCoreApplication_Init(PyObject* self, PyObject* args, PyObject*)
{
    if (Shiboken::isUserType(self) && !Shiboken::canCallConstructor(self->ob_type, Shiboken::SbkType<QApplication >()))
        return -1;


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

    QCoreApplicationWrapper* cptr = new QCoreApplicationWrapper(QCoreApplicationArgCount, QCoreApplicationArgValues);
    Shiboken::setCppPointer(reinterpret_cast<SbkBaseWrapper*>(self),
                            Shiboken::SbkType<QCoreApplication>(),
                            cptr);

    SbkBaseWrapper_setValidCppObject(self, 1);
    SbkBaseWrapper *sbkSelf = reinterpret_cast<SbkBaseWrapper*>(self);
    sbkSelf->containsCppWrapper = 1;
    sbkSelf->hasOwnership = 0;
    Shiboken::BindingManager::instance().registerWrapper(sbkSelf, cptr);
    PySide::signalUpdateSource(self);
    cptr->metaObject();

    PySide::registerCleanupFunction(DeleteQCoreApplicationAtExit);
    Py_INCREF(self);
    return 1;
}

// Borrowed reference to QtGui module
extern PyObject* moduleQtGui;

static int QApplicationArgCount;
static char** QApplicationArgValues;
static const char QAPP_MACRO[] = "qApp";

int Sbk_QApplication_Init(PyObject* self, PyObject* args, PyObject*)
{
    if (Shiboken::Object::isUserType(self) && !Shiboken::ObjectType::canCallConstructor(self->ob_type, Shiboken::SbkType<QApplication>()))
        return -1;

    if (QApplication::instance()) {
        PyErr_SetString(PyExc_RuntimeError, "A QApplication instance already exists.");
        return -1;
    }

    int numArgs = PyTuple_GET_SIZE(args);
    if (numArgs != 1) {
        PyErr_BadArgument();
        return -1;
    }

    if (!Shiboken::sequenceToArgcArgv(PyTuple_GET_ITEM(args, 0), &QApplicationArgCount, &QApplicationArgValues, "PySideApp")) {
        PyErr_BadArgument();
        return -1;
    }

    SbkObject* sbkSelf = reinterpret_cast<SbkObject*>(self);
    QApplicationWrapper* cptr = new QApplicationWrapper(QApplicationArgCount, QApplicationArgValues);
    Shiboken::Object::setCppPointer(sbkSelf,
                                     Shiboken::SbkType<QApplication>(),
                                     cptr);
    Shiboken::Object::setValidCpp(sbkSelf, true);
    Shiboken::Object::setHasCppWrapper(sbkSelf, true);
    Shiboken::Object::releaseOwnership(sbkSelf);
    Shiboken::BindingManager::instance().registerWrapper(sbkSelf, cptr);
    PySide::Signal::updateSourceObject(self);
    cptr->metaObject();

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
    return 1;
}

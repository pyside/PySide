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

    char** argv;
    int argc;
    if (!PySequence_to_argc_argv(PyTuple_GET_ITEM(args, 0), &argc, &argv)) {
        PyErr_BadArgument();
        return -1;
    }

    SbkBaseWrapper_setCptr(self, new QCoreApplication(argc, argv));
    SbkBaseWrapper_setValidCppObject(self, 1);
    Shiboken::BindingManager::instance().registerWrapper(reinterpret_cast<SbkBaseWrapper*>(self));
    return 1;
}

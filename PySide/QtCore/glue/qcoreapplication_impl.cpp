PyObject* SbkQCoreApplication_New(Shiboken::SbkBaseWrapperType* type, PyObject* args, PyObject*)
{
    int numArgs = PyTuple_GET_SIZE(args);
    if (numArgs != 1) {
        PyErr_BadArgument();
        return 0;
    }

    char** argv;
    int argc;
    if (!PySequence_to_argc_argv(PyTuple_GET_ITEM(args, 0), &argc, &argv)) {
        PyErr_BadArgument();
        return 0;
    }

    QCoreApplication* cptr = new QCoreApplication(argc, argv);
    PyObject* self = Shiboken::SbkBaseWrapper_New(type, cptr);

    if (!self) {
        if (cptr) delete cptr;
        PyErr_BadInternalCall();
        return 0;
    }
    return self;
}

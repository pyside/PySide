int SbkQApplication_Init(PyObject* self, PyObject* args, PyObject*)
{
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

    SbkBaseWrapper_setCptr(self, new QApplication(argc, argv));
    SbkBaseWrapper_setValidCppObject(self, 1);
    Shiboken::BindingManager::instance().registerWrapper(reinterpret_cast<SbkBaseWrapper*>(self));
    return 1;
}

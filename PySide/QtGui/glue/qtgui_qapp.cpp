// Init qApp macro to None.
Py_INCREF(Py_None);
PyModule_AddObject(module, "qApp", Py_None);
moduleQtGui = module;

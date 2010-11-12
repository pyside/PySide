QList<QByteArray> version = QByteArray(qVersion()).split('.');
PyObject *pyQtVersion = Shiboken::makeTuple(version[0].toInt(), version[1].toInt(), version[2].toInt());

PyModule_AddStringConstant(module, "__version__", qVersion());
PyModule_AddObject(module, "__version_info__", pyQtVersion);

inline PyObject*
addActionWithPyObject(QMenuBar* self, const QString& text, PyObject* callback)
{
    QAction* act = new QAction(text, self);

    self->addAction(act);

    PyObject* pyAct = Shiboken::Converter<QAction*>::toPython(act);
    PyObject* result = PyObject_CallMethod(pyAct, "connect", "OsO", pyAct,
                                           SIGNAL(triggered(bool)), callback);

    if (result == 0 || result == Py_False) {
        if (result)
            Py_DECREF(result);
        Py_DECREF(pyAct);
        return 0;
    }

    return pyAct;
}

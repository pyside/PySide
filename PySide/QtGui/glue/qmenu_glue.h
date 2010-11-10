
inline PyObject* addActionWithPyObject(QMenu* self, const QIcon& icon, const QString& text, PyObject* callback, const QKeySequence& shortcut)
{
    QAction* act = new QAction(text, self);

    if (!icon.isNull())
        act->setIcon(icon);

    if (!shortcut.isEmpty())
        act->setShortcut(shortcut);

    self->addAction(act);

    PyObject* pyAct = Shiboken::Converter<QAction*>::toPython(act);
    Shiboken::AutoDecRef result(PyObject_CallMethod(pyAct, "connect", "OsO", pyAct, SIGNAL(triggered()), callback));
    if (result.isNull()) {
        Py_DECREF(pyAct);
        return 0;
    }

    return pyAct;
}

/*
 * Based on code provided by:
 *          Antonio Valentino <antonio.valentino at tiscali.it>
 *          Frédéric <frederic.mantegazza at gbiloba.org>
 */

#include <shiboken.h>

static void
_populate_parent(PyObject* pyParent, QObject *parent)
{
    if (parent->children().isEmpty())
        return;

    foreach(QObject *child, parent->children()) {
        QString name(child->objectName());
        if (!name.isEmpty() && !name.startsWith("_") && !name.startsWith("qt_")) {
            bool has_attr = PyObject_HasAttrString(pyParent, qPrintable(name));
            Shiboken::AutoDecRef pyChild(Shiboken::Converter<QObject*>::toPython(child));
            if (!has_attr)
                PyObject_SetAttrString(pyParent, qPrintable(name), pyChild);

            Shiboken::Object::setParent(pyParent, pyChild);
            _populate_parent(pyChild, qobject_cast<QObject*>(child));
        }
    }
}

static PyObject*
quiloader_load_ui_from_device(QUiLoader* self, QIODevice* dev, QWidget *parent)
{
    QWidget *w = self->load(dev, parent);
    if (w) {
        QObject* _parent = parent;
        if (!_parent)
            _parent = w;

        if (parent && parent->layout())
            parent->layout()->deleteLater();

        PyObject* pyParent = Shiboken::Converter<QWidget*>::toPython(w);
        _populate_parent(pyParent, _parent);

        return pyParent;
    }

    if (!PyErr_Occurred())
        PyErr_SetString(PyExc_RuntimeError, "Unable to open ui file");
    return 0;
}

static PyObject*
quiloader_load_ui(QUiLoader* self, const QString &ui_file, QWidget *parent)
{
    QFile fd(ui_file);

    if (fd.exists(ui_file) && fd.open(QFile::ReadOnly)) {
        QWidget* w = self->load(&fd, parent);
        fd.close();
        if (w != 0) {
            QObject *_parent = parent;
            if (!_parent)
                _parent = w;

            Shiboken::AutoDecRef pyParent(Shiboken::Converter<QWidget*>::toPython(_parent));
            if (parent && parent->layout())
                parent->layout()->deleteLater();

            _populate_parent(pyParent, _parent);

            return Shiboken::Converter<QWidget*>::toPython(w);
        }
    }
    if (!PyErr_Occurred())
        PyErr_SetString(PyExc_RuntimeError, "Unable to open ui file");
    return 0;
}

/*
 * Based on code provided by:
 *          Antonio Valentino <antonio.valentino at tiscali.it>
 *          Frédéric <frederic.mantegazza at gbiloba.org>
 */

#include <shiboken.h>
#include <QUiLoader>
#include <QFile>
#include <QWidget>

static void createChildrenNameAttributes(PyObject* root, QObject* object)
{
    foreach (QObject* child, object->children()) {
        const QByteArray name = child->objectName().toLocal8Bit();

        if (!name.isEmpty() && !name.startsWith("_") && !name.startsWith("qt_")) {
            bool hasAttr = PyObject_HasAttrString(root, name.constData());
            if (!hasAttr) {
                Shiboken::AutoDecRef pyChild(Shiboken::Converter<QObject*>::toPython(child));
                PyObject_SetAttrString(root, name.constData(), pyChild);
            }
            createChildrenNameAttributes(root, child);
        }
        createChildrenNameAttributes(root, child);
    }
}

static PyObject* QUiLoadedLoadUiFromDevice(QUiLoader* self, QIODevice* dev, QWidget* parent)
{
    QWidget* wdg = self->load(dev, parent);

    if (wdg) {
        PyObject* pyWdg = Shiboken::Converter<QWidget*>::toPython(wdg);

        createChildrenNameAttributes(pyWdg, wdg);
        if (parent) {
            Shiboken::AutoDecRef pyParent(Shiboken::Converter<QWidget*>::toPython(parent));
            Shiboken::Object::setParent(pyParent, pyWdg);
        }

        return pyWdg;
    }

    if (!PyErr_Occurred())
        PyErr_SetString(PyExc_RuntimeError, "Unable to open/read ui device");
    return 0;
}

static PyObject* QUiLoaderLoadUiFromFileName(QUiLoader* self, const QString& uiFile, QWidget* parent)
{
    QFile fd(uiFile);
    return QUiLoadedLoadUiFromDevice(self, &fd, parent);
}

static QString retrieveObjectName(PyObject *obj)
{
    Shiboken::AutoDecRef objName(PyObject_Str(obj));
    return QString(PyString_AsString(objName));
}


/**
 * Tranfer objects ownership from layout to widget
 **/
static inline void qwidgetReparentLayout(QWidget *parent, QLayout *layout)
{
    Shiboken::AutoDecRef pyParent(Shiboken::Converter<QWidget*>::toPython(parent));

    for (int i=0; i < layout->count(); i++) {
        QLayoutItem* item = layout->itemAt(i);
        if (PyErr_Occurred())
            return;

        QWidget* w = item->widget();
        if (w) {
            QWidget* pw = w->parentWidget();
            if (pw != parent) {
                Shiboken::AutoDecRef pyChild(Shiboken::Converter<QWidget*>::toPython(w));
                Shiboken::setParent(pyParent, pyChild);
            }
        } else {
            QLayout* l = item->layout();
            if (l)
                qwidgetReparentLayout(parent, l);
        }
    }

    Shiboken::AutoDecRef pyChild(Shiboken::Converter<QLayout*>::toPython(layout));
    Shiboken::setParent(pyParent, pyChild);
    //remove previous references
    Shiboken::keepReference(reinterpret_cast<SbkObject*>(pyChild.object()), qPrintable(retrieveObjectName(pyChild)), Py_None);
}

static inline void qwidgetSetLayout(QWidget *self, QLayout *layout)
{
    if (!layout || self->layout())
        return;

    QObject* oldParent = layout->parent();
    if (oldParent && oldParent != self) {
        if (oldParent->isWidgetType()) {
            // remove old parent policy
            Shiboken::AutoDecRef pyLayout(Shiboken::Converter<QLayout*>::toPython(layout));
            Shiboken::setParent(Py_None, pyLayout);
        } else {
            PyErr_Format(PyExc_RuntimeError, "QWidget::setLayout: Attempting to set QLayout \"%s\" on %s \"%s\", when the QLayout already has a parent",
                          qPrintable(layout->objectName()), self->metaObject()->className(), qPrintable(self->objectName()));
            return;
        }
    }

    if (oldParent != self) {
        qwidgetReparentLayout(self, layout);
        if (PyErr_Occurred())
            return;

        self->setLayout(layout);
    }
}

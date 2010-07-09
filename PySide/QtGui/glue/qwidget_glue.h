static QString retrieveObjectName(PyObject *obj)
{
    Shiboken::AutoDecRef objName(PyObject_Str(obj));
    return QString(PyString_AsString(objName));
}


/**
 * Tranfer objects ownership from layout to widget
 **/
static inline void
qwidgetReparentLayout(QWidget *parent, QLayout *layout)
{
    Shiboken::AutoDecRef pyParent(Shiboken::Converter<QWidget*>::toPython(parent));

    for (int i=0; i < layout->count(); i++)
    {
        QLayoutItem *item = layout->itemAt(i);
        QWidget *w = item->widget();

        if (w)
        {
            Shiboken::AutoDecRef pyChild(Shiboken::Converter<QWidget*>::toPython(w));
            Shiboken::setParent(pyParent, pyChild);
        }
        else
        {
            QLayout *l = item->layout();
            if (l)
                qwidgetReparentLayout(parent, l);
        }
    }

    Shiboken::AutoDecRef pyChild(Shiboken::Converter<QLayout*>::toPython(layout));
    Shiboken::setParent(pyParent, pyChild);

    //remove previous references
    Shiboken::keepReference(reinterpret_cast<Shiboken::SbkBaseWrapper*>(pyChild.object()), qPrintable(retrieveObjectName(pyChild)), Py_None);
}

static inline void
qwidgetSetLayout(QWidget *self, QLayout *layout)
{
    if (self->layout())
        return;

    qwidgetReparentLayout(self, layout);
    self->setLayout(layout);
}

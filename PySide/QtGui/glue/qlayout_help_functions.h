#ifndef QLAYOUT_HELP_FUNCTIONS
#define QLAYOUT_HELP_FUNCTIONS

void addLayoutOwnership(QLayout* layout, QLayoutItem* item);

inline QByteArray retrieveObjectName(PyObject* obj)
{
    Shiboken::AutoDecRef objName(PyObject_Str(obj));
    return PyString_AsString(objName);
}

inline void addLayoutOwnership(QLayout* layout, QWidget* widget)
{
    //transfer ownership to parent widget
    QWidget* parent = layout->parentWidget();

    if (!parent) {
        //keep the reference while the layout is orphan
        Shiboken::AutoDecRef pyParent(Shiboken::Converter<QWidget*>::toPython(layout));
        Shiboken::AutoDecRef pyChild(Shiboken::Converter<QWidget*>::toPython(widget));
        Shiboken::Object::keepReference(reinterpret_cast<SbkObject*>(pyParent.object()), retrieveObjectName(pyParent).data(), pyChild, true);
    } else {
        Shiboken::AutoDecRef pyParent(Shiboken::Converter<QWidget*>::toPython(parent));
        Shiboken::AutoDecRef pyChild(Shiboken::Converter<QWidget*>::toPython(widget));
        Shiboken::Object::setParent(pyParent, pyChild);
    }
}

inline void addLayoutOwnership(QLayout* layout, QLayout* other)
{
    //transfer all children widgets from other to layout parent widget
    QWidget* parent = layout->parentWidget();
    if (!parent) {
        //keep the reference while the layout is orphan
        Shiboken::AutoDecRef pyParent(Shiboken::Converter<QLayout*>::toPython(layout));
        Shiboken::AutoDecRef pyChild(Shiboken::Converter<QLayout*>::toPython(other));
        Shiboken::Object::keepReference(reinterpret_cast<SbkObject*>(pyParent.object()), retrieveObjectName(pyParent).data(), pyChild, true);
        return;
    }

    for (int i=0, i_max=other->count(); i < i_max; i++) {
        QLayoutItem* item = layout->itemAt(i);
        if (PyErr_Occurred())
            return;

        addLayoutOwnership(layout, item);
    }

    Shiboken::AutoDecRef pyParent(Shiboken::Converter<QLayout*>::toPython(layout));
    Shiboken::AutoDecRef pyChild(Shiboken::Converter<QLayout*>::toPython(other));
    Shiboken::Object::setParent(pyParent, pyChild);

}

inline void addLayoutOwnership(QLayout* layout, QLayoutItem* item)
{
    QWidget* w = item->widget();
    if (w)
        addLayoutOwnership(layout, w);
    else {
        QLayout* l = item->layout();
        if (l)
            addLayoutOwnership(layout, l);
    }

    Shiboken::AutoDecRef pyParent(Shiboken::Converter<QLayout*>::toPython(layout));
    Shiboken::AutoDecRef pyChild(Shiboken::Converter<QLayoutItem*>::toPython(item));
    Shiboken::Object::setParent(pyParent, pyChild);
}

#endif

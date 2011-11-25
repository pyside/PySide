#ifndef QLAYOUT_HELP_FUNCTIONS
#define QLAYOUT_HELP_FUNCTIONS

void addLayoutOwnership(QLayout* layout, QLayoutItem* item);
void removeLayoutOwnership(QLayout* layout, QWidget* widget);

inline QByteArray retrieveObjectName(PyObject* obj)
{
    Shiboken::AutoDecRef objName(PyObject_Str(obj));
    return Shiboken::String::toCString(objName);
}

inline void addLayoutOwnership(QLayout* layout, QWidget* widget)
{
    //transfer ownership to parent widget
    QWidget *lw = layout->parentWidget();
    QWidget *pw = widget->parentWidget();

   Shiboken::AutoDecRef pyChild(Shiboken::Converter<QWidget*>::toPython(widget));

    //Transfer parent to layout widget 
    if (pw && lw && pw != lw)
        Shiboken::Object::setParent(0, pyChild);

    if (!lw && !pw) {
        //keep the reference while the layout is orphan
        Shiboken::AutoDecRef pyParent(Shiboken::Converter<QWidget*>::toPython(layout));
        Shiboken::Object::keepReference(reinterpret_cast<SbkObject*>(pyParent.object()), retrieveObjectName(pyParent).data(), pyChild, true);
    } else {
        if (!lw)
            lw = pw;

        Shiboken::AutoDecRef pyParent(Shiboken::Converter<QWidget*>::toPython(lw));
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
        QLayoutItem* item = other->itemAt(i);
        if (PyErr_Occurred() || !item)
            return;

        addLayoutOwnership(layout, item);
    }

    Shiboken::AutoDecRef pyParent(Shiboken::Converter<QLayout*>::toPython(layout));
    Shiboken::AutoDecRef pyChild(Shiboken::Converter<QLayout*>::toPython(other));
    Shiboken::Object::setParent(pyParent, pyChild);

}

inline void addLayoutOwnership(QLayout* layout, QLayoutItem* item)
{
    if (!item)
        return;

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

static void removeWidgetFromLayout(QLayout* layout, QWidget* widget)
{
    QWidget* parent = widget->parentWidget();

    if (!parent) {
        //remove reference on layout
        Shiboken::AutoDecRef pyParent(Shiboken::Converter<QWidget*>::toPython(layout));
        Shiboken::AutoDecRef pyChild(Shiboken::Converter<QWidget*>::toPython(widget));
        Shiboken::Object::removeReference(reinterpret_cast<SbkObject*>(pyParent.object()), retrieveObjectName(pyParent).data(), pyChild);
    } else {
        //give the ownership to parent
        Shiboken::AutoDecRef pyParent(Shiboken::Converter<QWidget*>::toPython(parent));
        Shiboken::AutoDecRef pyChild(Shiboken::Converter<QWidget*>::toPython(widget));
        Shiboken::Object::setParent(pyParent, pyChild);
    }
}

inline void removeLayoutOwnership(QLayout* layout, QLayoutItem* item)
{
    QWidget* w = item->widget();
    if (w)
        removeWidgetFromLayout(layout, w);
    else {
        QLayout* l = item->layout();
        if (l)
            removeLayoutOwnership(layout, l);
    }

    Shiboken::AutoDecRef pyChild(Shiboken::Converter<QLayoutItem*>::toPython(item));
    Shiboken::Object::invalidate(pyChild);
    Shiboken::Object::setParent(0, pyChild);
}

inline void removeLayoutOwnership(QLayout* layout, QWidget* widget)
{
    if (!widget)
        return;

    for (int i=0, i_max=layout->count(); i < i_max; i++) {
        QLayoutItem* item = layout->itemAt(i);
        if (PyErr_Occurred() || !item)
            return;
        if (item->widget() == widget)
            removeLayoutOwnership(layout, item);
    }
}

#endif

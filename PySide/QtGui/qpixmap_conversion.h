namespace Shiboken {
inline bool Converter< QPixmap >::isConvertible(PyObject* pyobj)
{
    bool isVariant = SbkQVariant_Check(pyobj);
    if (isVariant) {
        QVariant var(Converter<QVariant>::toCpp(pyobj));
        return var.type() == QVariant::Pixmap;
    } else if (SbkQSize_Check(pyobj) || SbkQString_Check(pyobj)) {
        return true;
    }
    return false;

}

inline QPixmap Converter< QPixmap >::toCpp(PyObject* pyobj)
{
    bool isVariant = SbkQVariant_Check(pyobj);
    if (isVariant) {
        QVariant var(Converter<QVariant>::toCpp(pyobj));
        return var.value<QPixmap>();
    } else if (SbkQSize_Check(pyobj)) {
        return QPixmap(Shiboken::Converter<QSize& >::toCpp(pyobj));
    } else if (SbkQString_Check(pyobj)) {
        return QPixmap(Shiboken::Converter<QString& >::toCpp(pyobj));
    }

    return *Converter<QPixmap*>::toCpp(pyobj);
}
}

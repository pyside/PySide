namespace Shiboken {
inline bool Converter< QPixmap >::isConvertible(PyObject* pyobj)
{
    SbkBaseWrapperType* shiboType = reinterpret_cast<SbkBaseWrapperType*>(SbkType<QPixmap>());
    bool isVariant = SbkQVariant_Check(pyobj);
    if (isVariant) {
        QVariant var(Converter<QVariant>::toCpp(pyobj));
        return var.type() == QVariant::Pixmap;
    } else if (SbkQSize_Check(pyobj) || SbkQString_Check(pyobj)) {
        return true;
    } else if (shiboType->ext_isconvertible) {
        return shiboType->ext_isconvertible(pyobj);
    }
    return false;

}

inline QPixmap Converter< QPixmap >::toCpp(PyObject* pyobj)
{
    SbkBaseWrapperType* shiboType = reinterpret_cast<SbkBaseWrapperType*>(SbkType<QPixmap>());
    bool isVariant = SbkQVariant_Check(pyobj);
    if (isVariant) {
        QVariant var(Converter<QVariant>::toCpp(pyobj));
        return var.value<QPixmap>();
    } else if (SbkQSize_Check(pyobj)) {
        return QPixmap(Shiboken::Converter<QSize& >::toCpp(pyobj));
    } else if (SbkQString_Check(pyobj)) {
        return QPixmap(Shiboken::Converter<QString& >::toCpp(pyobj));
    } else if (shiboType->ext_isconvertible && shiboType->ext_tocpp && shiboType->ext_isconvertible(pyobj)) {
        QPixmap* cptr = reinterpret_cast<QPixmap*>(shiboType->ext_tocpp(pyobj));
        std::auto_ptr<QPixmap> cptr_auto_ptr(cptr);
        return *cptr;
    }

    return *Converter<QPixmap*>::toCpp(pyobj);
}
}

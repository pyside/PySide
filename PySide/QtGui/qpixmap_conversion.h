namespace Shiboken {
inline bool Converter<QPixmap>::checkType(PyObject* pyObj)
{
    return ValueTypeConverter<QPixmap>::checkType(pyObj);
}

inline bool Converter<QPixmap>::isConvertible(PyObject* pyobj)
{
    if (ValueTypeConverter<QPixmap>::isConvertible(pyobj))
        return true;
    SbkBaseWrapperType* shiboType = reinterpret_cast<SbkBaseWrapperType*>(SbkType<QPixmap>());
    bool isVariant = Converter<QVariant>::checkType(pyobj);
    if (isVariant) {
        QVariant var(Converter<QVariant>::toCpp(pyobj));
        return var.type() == QVariant::Pixmap;
    } else if (Converter<QSize>::checkType(pyobj) || Converter<QString>::checkType(pyobj)) {
        return true;
    } else if (shiboType->ext_isconvertible) {
        return shiboType->ext_isconvertible(pyobj);
    }
    return false;

}

inline QPixmap Converter<QPixmap>::toCpp(PyObject* pyobj)
{
    SbkBaseWrapperType* shiboType = reinterpret_cast<SbkBaseWrapperType*>(SbkType<QPixmap>());
    bool isVariant = Converter<QVariant>::checkType(pyobj);
    if (isVariant) {
        QVariant var(Converter<QVariant>::toCpp(pyobj));
        return var.value<QPixmap>();
    } else if (Converter<QSize>::checkType(pyobj)) {
        return QPixmap(Shiboken::Converter<QSize >::toCpp(pyobj));
    } else if (Converter<QString>::checkType(pyobj)) {
        return QPixmap(Shiboken::Converter<QString >::toCpp(pyobj));
    } else if (shiboType->ext_isconvertible && shiboType->ext_tocpp && shiboType->ext_isconvertible(pyobj)) {
        QPixmap* cptr = reinterpret_cast<QPixmap*>(shiboType->ext_tocpp(pyobj));
        std::auto_ptr<QPixmap> cptr_auto_ptr(cptr);
        return *cptr;
    }

    return *Converter<QPixmap*>::toCpp(pyobj);
}

inline PyObject* Converter<QPixmap>::toPython(const QPixmap& cppObj)
{
    return ValueTypeConverter<QPixmap>::toPython(cppObj);
}
}

namespace Shiboken {
inline bool Converter<QPixmap>::checkType(PyObject* pyObj)
{
    return ValueTypeConverter<QPixmap>::checkType(pyObj);
}

inline bool Converter<QPixmap>::isConvertible(PyObject* pyobj)
{
    if (ValueTypeConverter<QPixmap>::isConvertible(pyobj))
        return true;
    SbkBaseType* shiboType = reinterpret_cast<SbkBaseType*>(SbkType<QPixmap>());
    bool isVariant = Converter<QVariant>::checkType(pyobj);
    if (isVariant) {
        QVariant var(Converter<QVariant>::toCpp(pyobj));
        return var.type() == QVariant::Pixmap;
    } else if (Converter<QSize>::checkType(pyobj) || Converter<QString>::checkType(pyobj)) {
        return true;
    } else {
        return Shiboken::BaseType::isExternalConvertible(shiboType, pyobj);
    }
    return false;

}

inline QPixmap Converter<QPixmap>::toCpp(PyObject* pyobj)
{
    SbkBaseType* shiboType = reinterpret_cast<SbkBaseType*>(SbkType<QPixmap>());
    bool isVariant = Converter<QVariant>::checkType(pyobj);
    if (isVariant) {
        QVariant var(Converter<QVariant>::toCpp(pyobj));
        return var.value<QPixmap>();
    } else if (Converter<QSize>::checkType(pyobj)) {
        return QPixmap(Shiboken::Converter<QSize >::toCpp(pyobj));
    } else if (Converter<QString>::checkType(pyobj)) {
        return QPixmap(Shiboken::Converter<QString >::toCpp(pyobj));
    } else if (Shiboken::BaseType::isExternalConvertible(shiboType, pyobj) && Shiboken::BaseType::hasExternalCppConversions(shiboType)) {
        QPixmap* cptr = reinterpret_cast<QPixmap*>(Shiboken::BaseType::callExternalCppConversion(shiboType, pyobj));
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

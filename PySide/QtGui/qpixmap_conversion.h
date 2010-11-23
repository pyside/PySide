namespace Shiboken {
inline bool Converter<QPixmap>::checkType(PyObject* pyObj)
{
    return ValueTypeConverter<QPixmap>::checkType(pyObj);
}

inline bool Converter<QPixmap>::isConvertible(PyObject* pyobj)
{
    if (ValueTypeConverter<QPixmap>::isConvertible(pyobj))
        return true;
    SbkObjectType* shiboType = reinterpret_cast<SbkObjectType*>(SbkType<QPixmap>());
    bool isVariant = Shiboken::Converter<QVariant>::checkType(pyobj);
    if (isVariant) {
        QVariant var(Shiboken::Converter<QVariant>::toCpp(pyobj));
        return var.type() == QVariant::Pixmap;
    } else if (Shiboken::Converter<QSize>::checkType(pyobj) || Shiboken::Converter<QString>::checkType(pyobj)) {
        return true;
    } else {
        return Shiboken::ObjectType::isExternalConvertible(shiboType, pyobj);
    }
    return false;

}

inline QPixmap Converter<QPixmap>::toCpp(PyObject* pyobj)
{
    SbkObjectType* shiboType = reinterpret_cast<SbkObjectType*>(SbkType<QPixmap>());
    bool isVariant = Converter<QVariant>::checkType(pyobj);
    if (isVariant) {
        QVariant var(Converter<QVariant>::toCpp(pyobj));
        return var.value<QPixmap>();
    } else if (Converter<QSize>::checkType(pyobj)) {
        return QPixmap(Shiboken::Converter<QSize >::toCpp(pyobj));
    } else if (Converter<QString>::checkType(pyobj)) {
        return QPixmap(Shiboken::Converter<QString >::toCpp(pyobj));
    } else if (Shiboken::ObjectType::isExternalConvertible(shiboType, pyobj) && Shiboken::ObjectType::hasExternalCppConversions(shiboType)) {
        QPixmap* cptr = reinterpret_cast<QPixmap*>(Shiboken::ObjectType::callExternalCppConversion(shiboType, pyobj));
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

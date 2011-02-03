namespace Shiboken {

inline bool Converter<QByteArray>::checkType(PyObject* pyObj)
{
    return ValueTypeConverter<QByteArray>::checkType(pyObj);
}

inline bool Converter<QByteArray>::isConvertible(PyObject* pyObj)
{
    if (ValueTypeConverter<QByteArray>::isConvertible(pyObj))
        return true;
    SbkObjectType* shiboType = reinterpret_cast<SbkObjectType*>(SbkType< ::QByteArray >());
    return Shiboken::Converter<const char *>::checkType(pyObj)
        || (ObjectType::isExternalConvertible(shiboType, pyObj));
}

inline QByteArray Converter<QByteArray>::toCpp(PyObject* pyObj)
{
    if (pyObj == Py_None)
        return 0;
    else if (PyObject_TypeCheck(pyObj, SbkType<QByteArray>()))
        return *Converter<QByteArray*>::toCpp(pyObj);
    else if (PyString_Check(pyObj))
        return QByteArray(PyString_AS_STRING(pyObj), PyString_GET_SIZE(pyObj));
    else
        return ValueTypeConverter<QByteArray>::toCpp(pyObj);
}

inline PyObject* Converter<QByteArray>::toPython(const ::QByteArray& cppObj)
{
    return ValueTypeConverter<QByteArray>::toPython(cppObj);
}

}

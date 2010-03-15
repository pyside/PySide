namespace Shiboken {
inline bool Shiboken::Converter<QChar >::isConvertible(PyObject* pyObj)
{
    return PyObject_TypeCheck(pyObj, SbkType<QChar>())
         || SbkPySide_QtCore_QChar_SpecialCharacter_Check(pyObj)
         || SbkQLatin1Char_Check(pyObj)
         || (PyString_Check(pyObj) && (PyString_Size(pyObj) == 1))
         || PyInt_Check(pyObj);
}

inline QChar Shiboken::Converter<QChar >::toCpp(PyObject* pyObj)
{
    if (!Shiboken_TypeCheck(pyObj, QChar)) {
        if (SbkPySide_QtCore_QChar_SpecialCharacter_Check(pyObj))
            return QChar(Shiboken::Converter<QChar::SpecialCharacter >::toCpp(pyObj));
        else if (SbkQLatin1Char_Check(pyObj))
            return QChar(Shiboken::Converter<QLatin1Char >::toCpp(pyObj));
        else if (PyString_Check(pyObj) && PyString_Size(pyObj) == 1)
            return QChar(Shiboken::Converter<char >::toCpp(pyObj));
        else if (PyInt_Check(pyObj))
            return QChar(Shiboken::Converter<int >::toCpp(pyObj));
    }
    return *Converter<QChar*>::toCpp(pyObj);
}

inline PyObject* Converter<QChar>::toPython(const QChar& cppObj)
{
    return ValueTypeConverter<QChar>::toPython(cppObj);
}
}

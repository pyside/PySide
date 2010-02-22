namespace Shiboken {

inline bool Shiboken::Converter<QChar >::isConvertible(PyObject* pyobj)
{
    return SbkPySide_QtCore_QChar_SpecialCharacter_Check(pyobj)
         || SbkQLatin1Char_Check(pyobj)
         || (PyString_Check(pyobj) && (PyString_Size(pyobj) == 1))
         || PyInt_Check(pyobj);
}

inline QChar Shiboken::Converter<QChar >::toCpp(PyObject* pyobj)
{
    if (!Shiboken_TypeCheck(pyobj, QChar)) {
        if (SbkPySide_QtCore_QChar_SpecialCharacter_Check(pyobj))
            return QChar(Shiboken::Converter<QChar::SpecialCharacter >::toCpp(pyobj));
        else if (SbkQLatin1Char_Check(pyobj))
            return QChar(Shiboken::Converter<QLatin1Char >::toCpp(pyobj));
        else if (PyString_Check(pyobj) && PyString_Size(pyobj) == 1)
            return QChar(Shiboken::Converter<char >::toCpp(pyobj));
        else if (PyInt_Check(pyobj))
            return QChar(Shiboken::Converter<int >::toCpp(pyobj));
    }
    return *SbkQChar_cptr(pyobj);
}
}

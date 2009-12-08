inline bool Converter< QString >::isConvertible(PyObject* pyobj)
{
    return PyString_Check(pyobj)
            || PyUnicode_Check(pyobj)
            || SbkQByteArray_Check(pyobj)
            || SbkQLatin1String_Check(pyobj)
            || SbkQChar_Check(pyobj);
}

inline QString* Converter<QString >::copyCppObject(const QString& cppobj)
{
    return new QString(cppobj);
}

inline PyObject* Converter< QString >::toPython(const QString& cppobj)
{
    return Converter< QString >::createWrapper(new QString(cppobj));
}

inline QString Converter< QString >::toCpp(PyObject* pyobj)
{
    if (SbkQChar_Check(pyobj)) {
        return QString(Converter< QChar >::toCpp(pyobj));
    } else if (SbkQByteArray_Check(pyobj)) {
        return QString(Converter< QByteArray >::toCpp(pyobj));
    } else if (SbkQLatin1String_Check(pyobj)) {
        return QString(Converter< QLatin1String >::toCpp(pyobj));
    } else if (PyUnicode_Check(pyobj)) {
        Py_UNICODE* unicode = PyUnicode_AS_UNICODE(pyobj);
#if defined(Py_UNICODE_WIDE)
        return QString::fromUcs4(unicode);
#else
        return QString::fromUtf16(unicode, PyUnicode_GET_SIZE(pyobj));
#endif
    } else if (PyString_Check(pyobj))
        return QString(Converter< char * >::toCpp(pyobj));
    return *SbkQString_cptr(pyobj);
}

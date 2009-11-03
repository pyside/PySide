inline bool Converter< QString >::isConvertible(PyObject* pyobj)
{
    return PyUnicode_Check(pyobj) || PyString_Check(pyobj);
}

inline PyObject* Converter< QString >::createWrapper(const QString* cppobj)
{
    return PyBaseWrapper_New(&PyQString_Type, &PyQString_Type, cppobj);
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
    if (PyQChar_Check(pyobj)) {
        return QString(Converter< QChar >::toCpp(pyobj));
    } else if (PyQByteArray_Check(pyobj)) {
        return QString(Converter< QByteArray >::toCpp(pyobj));
    } else if (PyQLatin1String_Check(pyobj)) {
        return QString(Converter< QLatin1String >::toCpp(pyobj));
    } else if (PyUnicode_Check(pyobj)) {
#if defined(Py_UNICODE_WIDE)
        Py_UNICODE* unicode = PyUnicode_AS_UNICODE(pyobj);
        return QString::fromUcs4(unicode);
#else
        PyObject* str = PyUnicode_AsUTF8String(pyobj);
        QString result = QString::fromUtf8(PyString_AS_STRING(str));
        Py_DECREF(str);
        return result;
#endif
    } else if (PyString_Check(pyobj))
        return QString(Converter< char * >::toCpp(pyobj));
    return *Converter< QString* >::toCpp(pyobj);
}

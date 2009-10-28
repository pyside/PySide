inline bool Converter< QString >::isConvertible(PyObject* pyObj)
{
    return PyObject_TypeCheck(pyObj, &PyQString_Type) || PyUnicode_Check(pyObj) || PyString_Check(pyObj);
}

inline PyObject* Converter< QString >::toPython(QString cppobj)
{
    PyObject* pyobj;
    void* holder = (void*) new QString(cppobj);
    pyobj = Shiboken::PyBaseWrapper_New(&PyQString_Type, &PyQString_Type, holder);
    return pyobj;
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
    return *((QString*) ((Shiboken::PyBaseWrapper*)pyobj)->cptr);
}

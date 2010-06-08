namespace Shiboken {

template<>
struct Converter<QChar>
{
    static bool checkType(PyObject* pyObj)
    {
        return PyString_Check(pyObj) && (PyString_Size(pyObj) == 1);
    }

    static bool isConvertible(PyObject* pyObj)
    {
        return (PyString_Check(pyObj) && (PyString_Size(pyObj) == 1))
               || pyObj == Py_None
               || PyInt_Check(pyObj);
    }

    static QChar toCpp(PyObject* pyObj)
    {
        if (PyString_Check(pyObj) && PyString_Size(pyObj) == 1)
            return QChar(Shiboken::Converter<char >::toCpp(pyObj));
        else if (PyInt_Check(pyObj))
            return QChar(Shiboken::Converter<int >::toCpp(pyObj));
        return QChar();
    }

    static PyObject* toPython(void* cppObj) { return toPython(*reinterpret_cast<QChar*>(cppObj)); }
    static PyObject* toPython(const QChar& cppObj)
    {
        wchar_t c = (wchar_t)cppObj.unicode();
        PyObject* pyObj = PyUnicode_FromWideChar(&c, 1);
        return pyObj;
    }
};
}

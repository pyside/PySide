namespace Shiboken {

template<>
inline PyTypeObject* SbkType<QString>()
{
    return &PyUnicode_Type;
}

template<>
struct Converter<QString>
{
    static bool checkType(PyObject* pyObj)
    {
        return Shiboken::String::check(pyObj);
    }

    static bool isConvertible(PyObject* pyObj)
    {
        return Shiboken::String::convertible(pyObj);
    }

    static QString toCpp(PyObject* pyObj)
    {
        if (PyUnicode_Check(pyObj)) {
            Py_UNICODE* unicode = PyUnicode_AS_UNICODE(pyObj);
    #if defined(Py_UNICODE_WIDE)
            // cast as Py_UNICODE can be a different type
            return QString::fromUcs4(reinterpret_cast<const uint*>(unicode));
    #else
            return QString::fromUtf16(unicode, PyUnicode_GET_SIZE(pyObj));
    #endif
        } else if (Shiboken::String::check(pyObj)) {
            return QString(Shiboken::String::toCString(pyObj));
        }
        return QString();
    }

    static PyObject* toPython(void* cppObj) { return toPython(*reinterpret_cast<QString*>(cppObj)); }
    static PyObject* toPython(const QString& cppObj)
    {
        const int N = cppObj.length();
        wchar_t* str = new wchar_t[N];
        cppObj.toWCharArray(str);
        PyObject* pyObj = PyUnicode_FromWideChar(str, N);
        delete[] str;
        return pyObj;
    }
};
}

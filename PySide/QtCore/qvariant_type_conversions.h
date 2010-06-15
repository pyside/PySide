namespace Shiboken {

template<>
struct Converter<QVariant::Type>
{
    static bool checkType(PyObject* pyObj)
    {
        return pyObj == Py_None || PyType_Check(pyObj) || Converter<QString>::checkType(pyObj);
    }

    static bool isConvertible(PyObject* pyObj)
    {
        return checkType(pyObj);
    }

    static QVariant::Type toCpp(PyObject* pyObj)
    {
        const char* typeName;
        if (pyObj == Py_None)
            return QVariant::Invalid;

        if (pyObj == reinterpret_cast<PyObject*>(&PyString_Type) || pyObj == reinterpret_cast<PyObject*>(&PyUnicode_Type))
            typeName = "QString";
        else if (pyObj == reinterpret_cast<PyObject*>(&PyFloat_Type))
            typeName = "double"; // float is a UserType in QVariant.
        else if (pyObj == reinterpret_cast<PyObject*>(&PyLong_Type))
            typeName = "int"; // long is a UserType in QVariant.
        else if (PyType_Check(pyObj))
            typeName = reinterpret_cast<PyTypeObject*>(pyObj)->tp_name;
        else if (PyString_Check(pyObj))
            typeName = PyString_AS_STRING(pyObj);
        else if (PyUnicode_Check(pyObj))
            typeName = PyString_AsString(pyObj);

        return QVariant::nameToType(typeName);
    }

    static PyObject* toPython(void* cppObj) { return toPython(*reinterpret_cast<QVariant::Type*>(cppObj)); }
    static PyObject* toPython(const QVariant::Type& cppObj)
    {
        const char* typeName = QVariant::typeToName(cppObj);
        PyObject* pyObj;
        if (!typeName) {
            pyObj = Py_None;
        } else {
            Shiboken::TypeResolver* tr = Shiboken::TypeResolver::get(typeName);
            pyObj = tr ? reinterpret_cast<PyObject*>(tr->pythonType()) : Py_None;
        }
        Py_INCREF(pyObj);
        return pyObj;
    }
};
}

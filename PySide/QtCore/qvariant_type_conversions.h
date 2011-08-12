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
        const char* typeName = 0;
        if (pyObj == Py_None)
            return QVariant::Invalid;

        if (Shiboken::String::checkType(reinterpret_cast<PyTypeObject*>(pyObj)))
            typeName = "QString";


        else if (pyObj == reinterpret_cast<PyObject*>(&PyFloat_Type))
            typeName = "double"; // float is a UserType in QVariant.
        else if (pyObj == reinterpret_cast<PyObject*>(&PyLong_Type))
            typeName = "int"; // long is a UserType in QVariant.
        else if (PyType_Check(pyObj)) {
            if (pyObj->ob_type == &SbkObjectType_Type)
                typeName = Shiboken::ObjectType::getOriginalName(reinterpret_cast<SbkObjectType*>(pyObj));
            else
                typeName = reinterpret_cast<PyTypeObject*>(pyObj)->tp_name;
        }
        else if (Shiboken::String::check(pyObj))
            typeName = Shiboken::String::toCString(pyObj);
        else if (PyDict_Check(pyObj) && checkAllStringKeys(pyObj))
            typeName = "QVariantMap";
        else if (PySequence_Check(pyObj))
            if (isStringList(pyObj))
                typeName = "QStringList";
            else
                typeName = "QVariantList";
        else
            Q_ASSERT(false);

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

    static bool isStringList(PyObject* list)
    {
        bool allString = true;
        AutoDecRef fast(PySequence_Fast(list, "Failed to convert QVariantList"));
        Py_ssize_t size = PySequence_Fast_GET_SIZE(fast.object());
        for(int i=0; i < size; i++) {
            PyObject* item = PySequence_Fast_GET_ITEM(fast.object(), i);
            if (!Converter<QString>::checkType(item)) {
                allString = false;
                break;
            }
        }
        return allString;
    }

    static bool checkAllStringKeys(PyObject* dict)
    {
        AutoDecRef keys(PyDict_Keys(dict));
        return isStringList(keys);
    }
};
}

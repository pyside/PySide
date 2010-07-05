namespace Shiboken {

template<>
struct Converter<QVariant>
{
    static bool checkType(PyObject* pyObj)
    {
        return false; // lets avoid the chaos
    }

    // all types are convertible to QVariant
    static bool isConvertible(PyObject* pyObj)
    {
        return true;
    }

    static QVariant toCpp(PyObject* pyObj)
    {
        using namespace Shiboken;

        // Primitive types
        if (Converter<bool>::checkType(pyObj)) {
            // QVariant(bool)
            return QVariant(Converter<bool>::toCpp(pyObj));
        } else if (pyObj == Py_None) {
            // QVariant()
            return QVariant();
        } else if (Converter<QString>::checkType(pyObj)) {
            // QVariant(const char*)
            return QVariant(Converter<QString>::toCpp(pyObj));
        } else if (PyFloat_CheckExact(pyObj)) {
            // QVariant(double)
            return QVariant(Converter<double>::toCpp(pyObj));
        } else if (PyInt_CheckExact(pyObj)) {
            // QVariant(int)
            return QVariant(Converter<int>::toCpp(pyObj));
        } else if (PyLong_CheckExact(pyObj)) {
            // QVariant(qlonglong)
            return QVariant(Converter<qlonglong>::toCpp(pyObj));
        } else if (Shiboken::isShibokenEnum(pyObj)) {
            // QVariant(enum)
            return QVariant(Converter<int>::toCpp(pyObj));
        } else if (!isShibokenType(pyObj) || isUserType(pyObj)) {
            // QVariant(User class)
            return QVariant::fromValue<PySide::PyObjectWrapper>(pyObj);
        } else {
            // a class supported by QVariant?
            if (Shiboken::isShibokenType(pyObj)) {
                Shiboken::SbkBaseWrapperType *objType = reinterpret_cast<Shiboken::SbkBaseWrapperType*>(pyObj->ob_type);
                const char* typeName = objType->original_name;
                uint typeCode = QMetaType::type(typeName);
                if (!typeCode) {// Try with star at end, for QObject*, QWidget* and QAbstractKinectScroller*
                    QString stypeName(typeName);
                    stypeName += '*';
                    typeCode = QMetaType::type(stypeName.toAscii());
                }
                if (typeCode)
                    return QVariant(typeCode, reinterpret_cast<SbkBaseWrapper*>(pyObj)->cptr[0]);
            }
            // Is a shiboken type not known by Qt
            return QVariant::fromValue<PySide::PyObjectWrapper>(pyObj);
        }
    }

    static PyObject* toPython(void* cppObj)
    {
        return toPython(*reinterpret_cast<QVariant*>(cppObj));
    }

    static PyObject* toPython(const QVariant& cppObj)
    {
        if (cppObj.isValid()) {
            Shiboken::TypeResolver* tr = Shiboken::TypeResolver::get(cppObj.typeName());
            if (tr)
                return tr->toPython(const_cast<void*>(cppObj.data()));
        }
        Py_RETURN_NONE;
    }
};
}

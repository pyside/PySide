// We use this thin wrapper instead of the plain PyObject pointer to avoid conflicts with specializations of T*
// in QVariant.
struct PyQt_PyObject
{
    PyObject* m_me;
    PyQt_PyObject(PyObject* me) : m_me(me) {}
    PyQt_PyObject() : m_me(Py_None) {}
    operator PyObject*() { return m_me; }
};

Q_DECLARE_METATYPE(PyQt_PyObject)

namespace Shiboken {

// all types are convertible to QVariant
inline bool Converter<QVariant>::isConvertible(PyObject* pyObj)
{
    return true;
}

inline QVariant Converter<QVariant>::toCpp(PyObject* pyObj)
{
    if (SbkQVariant_Check(pyObj))
        return *Converter<QVariant*>::toCpp(pyObj);

    // Primitive types
    if (PyBool_Check(pyObj)) {
        // QVariant(bool)
        return QVariant(Shiboken::Converter<bool>::toCpp(pyObj));
    } else if (PyString_CheckExact(pyObj)) {
        // QVariant(const char*)
        return QVariant(Shiboken::Converter<const char *>::toCpp(pyObj));
    } else if (PyFloat_CheckExact(pyObj)) {
        // QVariant(double)
        return QVariant(Shiboken::Converter<double>::toCpp(pyObj));
    } else if (PyInt_CheckExact(pyObj)) {
        // QVariant(int)
        return QVariant(Shiboken::Converter<int>::toCpp(pyObj));
    } else if (PyLong_CheckExact(pyObj)) {
        // QVariant(qlonglong)
        return QVariant(Shiboken::Converter<qlonglong>::toCpp(pyObj));
    } else if (Shiboken::isShibokenEnum(pyObj)) {
        // QVariant(enum)
        return QVariant(Shiboken::Converter<int>::toCpp(pyObj));
    } else if (!Shiboken::isShibokenType(pyObj) || Shiboken::isUserType(pyObj)) {
        // QVariant(User class)
        Py_INCREF(pyObj);
        return QVariant::fromValue<PyQt_PyObject>(pyObj);
    } else {
        // a class supported by QVariant?
        const char* typeName = pyObj->ob_type->tp_name;
        // check if the name starts with PySide.
        if (!strncmp("PySide.", typeName, 7)) {
            // get the type name
            const char* lastDot = typeName;
            for (int i = 8; typeName[i]; ++i) {
                if (typeName[i] == '.')
                    lastDot = &typeName[i];
            }
            lastDot++;
            uint typeCode = QMetaType::type(lastDot);
            if (!typeCode) {// Try with star at end, for QObject*, QWidget* and QAbstractKinectScroller*
                QString typeName(lastDot);
                typeName += '*';
                typeCode = QMetaType::type(typeName.toAscii());
            }
            if (typeCode)
                return QVariant(typeCode, reinterpret_cast<SbkBaseWrapper*>(pyObj)->cptr[0]);
        }
        // Is a shiboken type not known by Qt
        Py_INCREF(pyObj);
        return QVariant::fromValue<PyQt_PyObject>(pyObj);
    }
}

inline PyObject* Converter<QVariant>::toPython(const QVariant& cppObj)
{
    return ValueTypeConverter<QVariant>::toPython(cppObj);
}

}

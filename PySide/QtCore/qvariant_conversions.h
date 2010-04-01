// We use this thin wrapper instead of the plain PyObject pointer to avoid conflicts with specializations of T*
// in QVariant.
struct PyObjectHolder
{
    PyObject* m_me;
    PyObjectHolder(PyObject* me) : m_me(me) {}
    PyObjectHolder() : m_me(Py_None) {}
    operator PyObject*() { return m_me; }
};

/**
 * Q_DECLARE_METATYPE(PyObjectHolder);
 * Use the expanded version of Q_DECLARE_METATYPE macro to define a typename
 * compatible with PyQt4
 **/
QT_BEGIN_NAMESPACE
template <>
struct QMetaTypeId< PyObjectHolder >
{
    enum { Defined = 1 };
    static int qt_metatype_id()
    {
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0);
        if (!metatype_id)
            metatype_id =
                qRegisterMetaType<PyObjectHolder>("PyQt_PyObject");
        return metatype_id;
    }
};
QT_END_NAMESPACE

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
        return QVariant::fromValue<PyObjectHolder>(pyObj);
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
        return QVariant::fromValue<PyObjectHolder>(pyObj);
    }
}

inline PyObject* Converter<QVariant>::toPython(const QVariant& cppObj)
{
    return ValueTypeConverter<QVariant>::toPython(cppObj);
}

}

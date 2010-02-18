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

// all types are convertible to QVariant
inline bool Converter<QVariant>::isConvertible(PyObject* pyobj)
{
    return true;
}

inline QVariant Converter<QVariant>::toCpp(PyObject* pyobj)
{
    if (SbkQVariant_Check(pyobj))
        return *SbkQVariant_cptr(pyobj);
    // voodoo stuff to avoid linking qtcore bindings with qtgui bindings
    uint typeCode = QMetaType::type(pyobj->ob_type->tp_name);
    if (!typeCode || typeCode > QVariant::UserType) {

            // Check the implicit conversion stuff for most python-native types
            if (SbkPySide_QtCore_QVariant_Type_CheckExact(pyobj)) {
                QVariant::Type cpp_arg0 = Shiboken::Converter<QVariant::Type >::toCpp(pyobj);
                // QVariant(QVariant::Type)
                return QVariant(cpp_arg0);
            } else if (SbkPySide_QtCore_Qt_GlobalColor_CheckExact(pyobj)) {
                Qt::GlobalColor cpp_arg0 = Shiboken::Converter<Qt::GlobalColor >::toCpp(pyobj);
                // QVariant(Qt::GlobalColor)
                return QVariant(cpp_arg0);
            } else if (PyBool_Check(pyobj)) {
                bool cpp_arg0 = Shiboken::Converter<bool >::toCpp(pyobj);
                // QVariant(bool)
                return QVariant(cpp_arg0);
            } else if (PyString_Check(pyobj)) {
                const char * cpp_arg0 = Shiboken::Converter<const char * >::toCpp(pyobj);
                // QVariant(const char*)
                return QVariant(cpp_arg0);
            } else if (PyFloat_Check(pyobj)) {
                double cpp_arg0 = Shiboken::Converter<double >::toCpp(pyobj);
                // QVariant(double)
                return QVariant(cpp_arg0);
            } else if (PyNumber_Check(pyobj)) {
                int cpp_arg0 = Shiboken::Converter<int >::toCpp(pyobj);
                // QVariant(int)
                return QVariant(cpp_arg0);
            } else if (PyLong_Check(pyobj)) {
                qlonglong cpp_arg0 = Shiboken::Converter<qlonglong >::toCpp(pyobj);
                // QVariant(qlonglong)
                return QVariant(cpp_arg0);
            } else {
                Py_INCREF(pyobj);
                return QVariant::fromValue<PyObjectHolder>(pyobj);
            }
    } else {
        // Is a known Qt type
        return QVariant(typeCode, reinterpret_cast<SbkBaseWrapper*>(pyobj)->cptr);
    }
}

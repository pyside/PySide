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
bool Shiboken::Converter<QVariant>::isConvertible(PyObject* pyobj)
{
    return true;
}

PyObject* Shiboken::Converter<QVariant>::toPython(const QVariant& cppobj)
{
    return Converter<QVariant>::createWrapper(new QVariant(cppobj));
}

QVariant* Shiboken::Converter<QVariant>::copyCppObject(const QVariant& cppobj)
{
    return new QVariant(cppobj);
}

QVariant Shiboken::Converter<QVariant>::toCpp(PyObject* pyobj)
{
    if (SbkQVariant_Check(pyobj))
        return *SbkQVariant_cptr(pyobj);
    // voodoo stuff to avoid linking qtcore bindings with qtgui bindings
    uint typeCode = QMetaType::type(pyobj->ob_type->tp_name);
    if (!typeCode || typeCode > QVariant::UserType) {
        Py_INCREF(pyobj);
        return QVariant::fromValue<PyObjectHolder>(pyobj);
    } else {
        // Is a known Qt type
        return QVariant(typeCode, reinterpret_cast<SbkBaseWrapper*>(pyobj)->cptr);
    }
}

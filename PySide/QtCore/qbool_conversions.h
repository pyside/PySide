namespace Shiboken {
template <>
struct Converter<QBool> : public ValueTypeConverter<QBool>
{
    using ValueTypeConverter<QBool>::toPython;

    static PyObject* toPython(const QBool& cppobj)
    {
        return PyBool_FromLong((bool) cppobj);
    }
    static QBool toCpp(PyObject* pyobj)
    {
        return QBool(pyobj == Py_True);
    }
};
}

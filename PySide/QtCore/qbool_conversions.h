template <>
struct Converter<QBool> : public ConverterBase<QBool>
{
    using ConverterBase<QBool>::toPython;

    static PyObject* toPython(const QBool& cppobj)
    {
        return PyBool_FromLong((bool) cppobj);
    }
    static QBool toCpp(PyObject* pyobj)
    {
        return QBool(pyobj == Py_True);
    }
};

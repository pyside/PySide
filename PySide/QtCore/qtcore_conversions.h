
template <>
struct Converter<QBool>
{
    static PyObject* toPython(ValueHolder<QBool> holder)
    {
        return PyBool_FromLong((bool)holder.value);
    }
    static QBool toCpp(PyObject* pyobj)
    {
        return QBool(pyobj == Py_True);
    }
};

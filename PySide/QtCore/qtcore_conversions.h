
template <>
struct Converter<QBool>
{
    static PyObject* toPython(QBool holder)
    {
        return PyBool_FromLong(bool(holder));
    }
    static QBool toCpp(PyObject* pyobj)
    {
        return QBool(pyobj == Py_True);
    }
};

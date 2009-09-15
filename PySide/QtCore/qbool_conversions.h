
template <>
struct Converter<QBool>
{
    static PyObject* toPython(QBool cppobj)
    {
        return PyBool_FromLong((bool) cppobj);
    }
    static QBool toCpp(PyObject* pyobj)
    {
        return QBool(pyobj == Py_True);
    }
};

template <typename qpair>
struct Converter_qpair
{
    static bool isConvertible(const PyObject* pyObj) {
        return PySequence_Check(const_cast<PyObject*>(pyObj));
    }
    static PyObject* toPython(qpair holder)
    {
        typename qpair::first_type first(holder.first);
        typename qpair::second_type second(holder.second);
        PyObject* tuple = PyTuple_New(2);
        PyTuple_SET_ITEM(tuple, 0, Converter<typename qpair::first_type>::toPython(first));
        PyTuple_SET_ITEM(tuple, 1, Converter<typename qpair::second_type>::toPython(second));
        return tuple;
    }
    static qpair toCpp(PyObject* pyobj)
    {
        qpair result;
        PyObject* pyFirst = PySequence_GetItem(pyobj, 0);
        PyObject* pySecond = PySequence_GetItem(pyobj, 1);
        result.first = Converter<typename qpair::first_type>::toCpp(pyFirst);
        result.second = Converter<typename qpair::second_type>::toCpp(pySecond);
        return result;
    }
};

template<typename FT, typename ST>
struct Converter<QPair<FT, ST> > : Converter_qpair<QPair<FT, ST> > {};

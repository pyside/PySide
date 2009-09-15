template <typename StdPair>
struct Converter_qpair
{
    static PyObject* toPython(StdPair holder)
    {
        typename StdPair::first_type first(holder.first);
        typename StdPair::second_type second(holder.second);
        PyObject* tuple = PyTuple_New(2);
        PyTuple_SET_ITEM(tuple, 0, Converter<typename StdPair::first_type>::toPython(first));
        PyTuple_SET_ITEM(tuple, 1, Converter<typename StdPair::second_type>::toPython(second));
        return tuple;
    }
    static StdPair toCpp(PyObject* pyobj)
    {
        StdPair result;
        PyObject* pyFirst = PySequence_GetItem(pyobj, 0);
        PyObject* pySecond = PySequence_GetItem(pyobj, 1);
        result.first = Converter<typename StdPair::first_type>::toCpp(pyFirst);
        result.second = Converter<typename StdPair::second_type>::toCpp(pySecond);
        return result;
    }
};

template<typename FT, typename ST>
struct Converter<QPair<FT, ST> > : Converter_qpair<QPair<FT, ST> > {};

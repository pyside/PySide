template <typename StdList>
struct Converter_qlist
{
    static PyObject* toPython(StdList holder)
    {
        PyObject* result = PyList_New(holder.size());
        for (int i = 0; i < holder.size(); i++) {
            PyList_SET_ITEM(result, i, Converter<typename StdList::value_type>::toPython(holder.at(i)));
        }
        return result;
    }
    static StdList toCpp(PyObject* pyobj)
    {
        StdList result;
        for (int i = 0; i < PySequence_Size(pyobj); i++) {
            PyObject* pyItem = PySequence_GetItem(pyobj, i);
            result.append(Converter<typename StdList::value_type>::toCpp(pyItem));
        }
        return result;
    }
};

template<typename T>
struct Converter<QList<T> > : Converter_qlist<QList<T> > {};

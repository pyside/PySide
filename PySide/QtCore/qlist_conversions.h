template <typename qlist>
struct Converter_qlist
{
    static bool isConvertible(PyObject* pyobj) {
        return PySequence_Check(pyobj);
    }

    static PyObject* toPython(const qlist& list)
    {
        PyObject* result = PyList_New(list.size());
        for (int i = 0; i < list.size(); i++) {
            PyList_SET_ITEM(result, i, Converter<typename qlist::value_type>::toPython(list.at(i)));
        }
        return result;
    }
    static qlist toCpp(PyObject* pyobj)
    {
        qlist result;
        for (int i = 0; i < PySequence_Size(pyobj); i++) {
            PyObject* pyItem = PySequence_GetItem(pyobj, i);
            result.append(Converter<typename qlist::value_type>::toCpp(pyItem));
        }
        return result;
    }
};

template<typename T>
struct Converter<QList<T> > : Converter_qlist<QList<T> > {};

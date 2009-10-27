template <typename qlist>
struct Converter_qlist
{
    static bool isConvertible(const PyObject* pyObj) {
        return PySequence_Check(const_cast<PyObject*>(pyObj));
    }

    static PyObject* toPython(const qlist holder)
    {
        PyObject* result = PyList_New(holder.size());
        for (int i = 0; i < holder.size(); i++) {
            PyList_SET_ITEM(result, i, Converter<typename qlist::value_type>::toPython(holder.at(i)));
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

template <typename qvector>
struct Converter_qvector
{
    static bool isConvertible(PyObject* pyobj) {
        return PySequence_Check(pyobj);
    }
    static PyObject* toPython(const qvector& vector)
    {
        PyObject* result = PyList_New(vector.size());
        for (int i = 0; i < vector.size(); i++) {
            PyList_SET_ITEM(result, i, Converter<typename qvector::value_type>::toPython(vector.at(i)));
        }
        return result;
    }
    static qvector toCpp(PyObject* pyobj)
    {
        qvector result;
        for (int i = 0; i < PySequence_Size(pyobj); i++) {
            PyObject* pyItem = PySequence_GetItem(pyobj, i);
            result.append(Converter<typename qvector::value_type>::toCpp(pyItem));
        }
        return result;
    }
};

template<typename T>
struct Converter<QVector<T> > : Converter_qvector<QVector<T> > {};

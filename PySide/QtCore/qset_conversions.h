namespace Shiboken {
template <typename qset>
struct Converter_qset
{
    static bool isConvertible(PyObject* pyobj) {
        return PyIter_Check(pyobj);
    }

    static PyObject* toPython(const qset& set)
    {
        PyObject* result = PySet_New(NULL);
        foreach(typename qset::value_type x, set)  {
            PyObject *pyObj = Converter<typename qset::value_type>::toPython(x);
            PySet_Add(result, pyObj);
            Py_DECREF(pyObj);
        }
        return result;
    }
    static qset toCpp(PyObject* pyobj)
    {
        qset result;
        PyObject *iterator = PyObject_GetIter(pyobj);

        if (iterator == NULL)
            return NULL;

        PyObject *pyItem = NULL;
        while (pyItem = PyIter_Next(iterator)) {
            result.insert(Converter<typename qset::value_type>::toCpp(pyItem));
            Py_DECREF(pyItem);
        }

        Py_XDECREF(iterator);

        if (PyErr_Occurred())
            return NULL;

        return result;
    }
};

template<typename T>
struct Converter<QSet<T> > : Converter_qset<QSet<T> > {};
}

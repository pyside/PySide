template <typename qhash>
struct Converter_qhash
{
    static bool isConvertible(PyObject* pyObj) {
        return PyDict_Check(pyObj);
    }

    static PyObject* toPython(qhash hash)
    {
        PyObject* result = PyDict_New();

        QHashIterator<typename qhash::key_type, typename qhash::mapped_type> it(hash);
        while (it.hasNext()) {
            it.next();
            PyDict_SetItem(result,
                           Converter<typename qhash::key_type>::toPython(it.key()),
                           Converter<typename qhash::mapped_type>::toPython(it.value()));
        }

        return result;
    }
    static qhash toCpp(PyObject* pyobj)
    {
        qhash result;

        PyObject* key;
        PyObject* value;
        Py_ssize_t pos = 0;

        Py_INCREF(pyobj);

        while (PyDict_Next(pyobj, &pos, &key, &value)) {
            result.insert(Converter<typename qhash::key_type>::toCpp(key),
                          Converter<typename qhash::mapped_type>::toCpp(value));
        }

        Py_DECREF(pyobj);

        return result;
    }
};

template<typename KT, typename VT>
struct Converter<QHash<KT, VT> > : Converter_qhash<QHash<KT, VT> > {};

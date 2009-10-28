template <typename qmap>
struct Converter_qmap
{
    static bool isConvertible(PyObject* pyObj) {
        return PyDict_Check(pyObj);
    }

    static PyObject* toPython(qmap map)
    {
        PyObject* result = PyDict_New();

        QMapIterator<typename qmap::key_type, typename qmap::mapped_type> it(map);
        while (it.hasNext()) {
            it.next();
            PyDict_SetItem(result,
                           Converter<typename qmap::key_type>::toPython(it.key()),
                           Converter<typename qmap::mapped_type>::toPython(it.value()));
        }

        return result;
    }
    static qmap toCpp(PyObject* pyobj)
    {
        qmap result;

        PyObject* key;
        PyObject* value;
        Py_ssize_t pos = 0;

        Py_INCREF(pyobj);

        while (PyDict_Next(pyobj, &pos, &key, &value)) {
            result.insert(Converter<typename qmap::key_type>::toCpp(key),
                          Converter<typename qmap::mapped_type>::toCpp(value));
        }

        Py_DECREF(pyobj);

        return result;
    }
};

template<typename KT, typename VT>
struct Converter<QMap<KT, VT> > : Converter_qmap<QMap<KT, VT> > {};

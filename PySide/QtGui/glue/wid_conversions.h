#ifndef Q_WS_WIN

namespace Shiboken {
template <>
struct Converter<WId>
{
    static bool checkType(PyObject* pyObj)
    {
        return false;
    }

    static bool isConvertible(PyObject* pyobj)
    {
        return pyobj == Py_None || PyNumber_Check(pyobj);
    }

    static inline PyObject* toPython(void* cppobj)
    {
        // not supported
        Q_ASSERT(true);
        return 0;
    }

    static PyObject* toPython(WId cppobj)
    {
        return PyLong_FromVoidPtr((void*)cppobj);
    }

    static WId toCpp(PyObject* pyobj)
    {
        if (pyobj == Py_None)
            return 0;
        return (WId)PyLong_AsVoidPtr(pyobj);
    }
};

}

#endif

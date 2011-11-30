namespace Shiboken {
template <>
struct Converter<HWND>
{
    static bool checkType(PyObject* pyObj)
    {
        return false;
    }

    static bool isConvertible(PyObject* pyobj)
    {
        if (pyobj == Py_None)
            return true;
#ifdef IS_PY3K
        return PyCapsule_CheckExact(pyobj);
#else
        return PyCObject_Check(pyobj);
#endif
    }

    static inline PyObject* toPython(void* cppobj)
    {
        // not supported
        Q_ASSERT(true);
        return 0;
    }

    static PyObject* toPython(HWND cppobj)
    {
        if (!cppobj)
            Py_RETURN_NONE;
#ifdef IS_PY3K
        return PyCapsule_New(cppobj, 0, 0);
#else
        return PyCObject_FromVoidPtr(cppobj, 0);
#endif
    }

    static HWND toCpp(PyObject* pyobj)
    {
        if (pyobj == Py_None)
            return (HWND) 0;
#ifdef IS_PY3K
        return (HWND)PyCapsule_GetPointer(pyobj, 0);
#else
        return (HWND)PyCObject_AsVoidPtr(pyobj);
#endif
    }
};
}

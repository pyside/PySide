namespace Shiboken {
template <>
struct Converter<HWND__>
{
    static bool checkType(PyObject* pyObj)
    {
        return false;
    }

    static bool isConvertible(PyObject* pyobj)
    {
        return PyCObject_Check(pyobj);
    }

    static inline PyObject* toPython(void* cppobj)
    {
        // not supported
        Q_ASSERT(true);
        return 0;
    }

    static PyObject* toPython(HWND__ cppobj)
    {
        return PyCObject_FromVoidPtr(&cppobj, 0);
    }

    static HWND__ toCpp(PyObject* pyobj)
    {
        return *((HWND__*) PyCObject_AsVoidPtr(pyobj));
    }
};
}

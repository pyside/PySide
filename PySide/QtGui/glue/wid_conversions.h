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
        return PyCObject_Check(pyobj);
    }

    static inline PyObject* toPython(void* cppobj)
    {
        // not supported
        Q_ASSERT(true);
        return 0;
    }

    static PyObject* toPython(WId cppobj)
    {
        return PyCObject_FromVoidPtr(cppobj, 0);
    }

    static WId toCpp(PyObject* pyobj)
    {
        return (WId) PyCObject_AsVoidPtr(pyobj);
    }
};
}
#endif

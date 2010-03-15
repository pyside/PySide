namespace Shiboken
{
inline bool Converter<QStringList>::isConvertible(PyObject* pyObj)
{
    return StdListConverter<QStringList>::isConvertible(pyObj);
}

inline QStringList Converter<QStringList>::toCpp(PyObject* pyObj)
{
    return StdListConverter<QStringList>::toCpp(pyObj);
}

inline PyObject* Converter<QStringList>::toPython(const QStringList& cppObj)
{
    return StdListConverter<QStringList>::toPython(cppObj);
}
}

namespace Shiboken
{
inline bool Converter<QStringList>::checkType(PyObject* pyObj)
{
    return Converter_std_list<QStringList>::checkType(pyObj);
}

inline bool Converter<QStringList>::isConvertible(PyObject* pyObj)
{
    return Converter_std_list<QStringList>::isConvertible(pyObj);
}

inline QStringList Converter<QStringList>::toCpp(PyObject* pyObj)
{
    return Converter_std_list<QStringList>::toCpp(pyObj);
}

inline PyObject* Converter<QStringList>::toPython(const QStringList& cppObj)
{
    return Converter_std_list<QStringList>::toPython(cppObj);
}
}

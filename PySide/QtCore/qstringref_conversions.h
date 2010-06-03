namespace Shiboken {

template<>
struct Converter<QStringRef> : public Converter<QString>
{
    static PyObject* toPython(void* cppObj) { return toPython(*reinterpret_cast<QStringRef*>(cppObj)); }

    static PyObject* toPython(const QStringRef& cppObj)
    {
        const QString* str = cppObj.string();
        return Converter<QString>::toPython(*str);
    }

    static QStringRef toCpp(PyObject* pyObj)
    {
        return QStringRef();
    }
};
}

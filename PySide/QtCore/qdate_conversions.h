namespace Shiboken {

inline bool Converter<QDate>::checkType(PyObject* pyObj)
{
    return ValueTypeConverter<QDate>::checkType(pyObj);
}

inline PyObject* Converter<QDate>::toPython(const ::QDate& cppObj)
{
    return ValueTypeConverter<QDate>::toPython(cppObj);
}

inline bool Converter<QDate>::isConvertible(PyObject* pyObj)
{
    if (ValueTypeConverter<QDate>::isConvertible(pyObj))
        return true;

    if (!PyDateTimeAPI)
        PyDateTime_IMPORT;

    SbkObjectType* shiboType = reinterpret_cast<SbkObjectType*>(SbkType< ::QDate >());
    return PyDate_Check(pyObj) || ObjectType::isExternalConvertible(shiboType, pyObj);
}

inline QDate Converter<QDate>::toCpp(PyObject* pyObj)
{
    if (!PyDateTimeAPI)
        PyDateTime_IMPORT;

    if (pyObj == Py_None) {
        return QDate();
    } else if (PyObject_TypeCheck(pyObj, SbkType<QDate>())) {
        return *Converter<QDate*>::toCpp(pyObj);
    } else if (PyDate_Check(pyObj)) {
        int day = PyDateTime_GET_DAY(pyObj);
        int month = PyDateTime_GET_MONTH(pyObj);
        int year = PyDateTime_GET_YEAR(pyObj);
        return QDate(year, month, day);
    } else {
        return ValueTypeConverter<QDate>::toCpp(pyObj);
    }
}


}

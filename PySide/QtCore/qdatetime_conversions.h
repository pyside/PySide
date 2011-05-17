namespace Shiboken {

inline bool Converter<QDateTime>::checkType(PyObject* pyObj)
{
    return ValueTypeConverter<QDateTime>::checkType(pyObj);
}

inline PyObject* Converter<QDateTime>::toPython(const ::QDateTime& cppObj)
{
    return ValueTypeConverter<QDateTime>::toPython(cppObj);
}

inline bool Converter<QDateTime>::isConvertible(PyObject* pyObj)
{
    if (ValueTypeConverter<QDateTime>::isConvertible(pyObj))
        return true;

    if (!PyDateTimeAPI)
        PyDateTime_IMPORT;

    SbkObjectType* shiboType = reinterpret_cast<SbkObjectType*>(SbkType< ::QDateTime >());
    return PyDateTime_Check(pyObj) || ObjectType::isExternalConvertible(shiboType, pyObj);
}


inline QDateTime Converter<QDateTime>::toCpp(PyObject* pyObj)
{
    if (!PyDateTimeAPI)
        PyDateTime_IMPORT;

    if (pyObj == Py_None) {
        return QDateTime();
    } else if (PyObject_TypeCheck(pyObj, SbkType<QDateTime>())) {
        return *Converter<QDateTime*>::toCpp(pyObj);
    } else if (PyDateTime_Check(pyObj)) {
        int day = PyDateTime_GET_DAY(pyObj);
        int month = PyDateTime_GET_MONTH(pyObj);
        int year = PyDateTime_GET_YEAR(pyObj);
        int hour = PyDateTime_DATE_GET_HOUR(pyObj);
        int min = PyDateTime_DATE_GET_MINUTE(pyObj);
        int sec = PyDateTime_DATE_GET_SECOND(pyObj);
        int msec = PyDateTime_DATE_GET_MICROSECOND(pyObj);
        return QDateTime(QDate(year, month, day), QTime(hour, min, sec, msec));
    } else {
        return ValueTypeConverter<QDateTime>::toCpp(pyObj);
    }
}

}

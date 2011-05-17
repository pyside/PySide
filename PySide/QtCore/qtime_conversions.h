namespace Shiboken {

inline bool Converter<QTime>::checkType(PyObject* pyObj)
{
    return ValueTypeConverter<QTime>::checkType(pyObj);
}

inline PyObject* Converter<QTime>::toPython(const ::QTime& cppObj)
{
    return ValueTypeConverter<QTime>::toPython(cppObj);
}

inline bool Converter<QTime>::isConvertible(PyObject* pyObj)
{
    if (ValueTypeConverter<QTime>::isConvertible(pyObj))
        return true;

    if (!PyDateTimeAPI)
        PyDateTime_IMPORT;

    SbkObjectType* shiboType = reinterpret_cast<SbkObjectType*>(SbkType< ::QTime >());
    return PyTime_Check(pyObj) || ObjectType::isExternalConvertible(shiboType, pyObj);
}

inline QTime Converter<QTime>::toCpp(PyObject* pyObj)
{
    if (!PyDateTimeAPI)
        PyDateTime_IMPORT;

    if (pyObj == Py_None) {
        return QTime();
    } else if (PyObject_TypeCheck(pyObj, SbkType<QTime>())) {
        return *Converter<QTime*>::toCpp(pyObj);
    } else  if (PyTime_Check(pyObj)) {
        int hour = PyDateTime_TIME_GET_HOUR(pyObj);
        int min = PyDateTime_TIME_GET_MINUTE(pyObj);
        int sec = PyDateTime_TIME_GET_SECOND(pyObj);
        int msec = PyDateTime_TIME_GET_MICROSECOND(pyObj);
        return QTime(hour, min, sec, msec);
    } else {
        return ValueTypeConverter<QTime>::toCpp(pyObj);
    }
}

}

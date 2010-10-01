namespace Shiboken {
template <>
struct PythonConverter<QTime>
{
    static bool isPythonConvertible(PyObject* pyObj)
    {
        if (!PyDateTimeAPI)
            PyDateTime_IMPORT;

        return pyObj && PyTime_Check(pyObj);
    }

    static QTime* transformFromPython(PyObject* obj)
    {
        if (isPythonConvertible(obj)) {
            int hour = PyDateTime_TIME_GET_HOUR(obj);
            int min = PyDateTime_TIME_GET_MINUTE(obj);
            int sec = PyDateTime_TIME_GET_SECOND(obj);
            int msec = PyDateTime_TIME_GET_MICROSECOND(obj);
            return new QTime(hour, min, sec, msec);
        }
        return 0;
    }

    static PyObject* transformToPython(QTime* d)
    {
        if (d) {
            if (!PyDateTimeAPI) 
                PyDateTime_IMPORT;

            return PyTime_FromTime(d->hour(), d->minute(), d->second(), d->msec());
        }
        return 0;
    }
};
}

namespace Shiboken {
template <>
struct PythonConverter<QDateTime>
{
    static bool isPythonConvertible(PyObject* pyObj)
    {
        if (!PyDateTimeAPI)
            PyDateTime_IMPORT;

        return pyObj && PyDateTime_Check(pyObj);
    }

    static QDateTime* transformFromPython(PyObject* obj)
    {
        if (isPythonConvertible(obj)) {
            int day = PyDateTime_GET_DAY(obj);
            int month = PyDateTime_GET_MONTH(obj);
            int year = PyDateTime_GET_YEAR(obj);
            int hour = PyDateTime_DATE_GET_HOUR(obj);
            int min = PyDateTime_DATE_GET_MINUTE(obj);
            int sec = PyDateTime_DATE_GET_SECOND(obj);
            int msec = PyDateTime_DATE_GET_MICROSECOND(obj);
            return new QDateTime(QDate(year, month, day), QTime(hour, min, sec, msec));
        }
        return 0;
    }

    static PyObject* transformToPython(QDateTime* d)
    {
        if (d) {
            if (!PyDateTimeAPI) 
                PyDateTime_IMPORT;

            QDate date = d->date();
            QTime time = d->time();
            return PyDateTime_FromDateAndTime(date.year(), date.month(), date.day(), time.hour(), time.minute(), time.second(), time.msec());
        }
        return 0;
    }
};
}

namespace Shiboken {
template <>
struct PythonConverter<QDate>
{
    static bool isPythonConvertible(PyObject* pyObj)
    {
        if (!PyDateTimeAPI)
            PyDateTime_IMPORT;

        return pyObj && PyDate_Check(pyObj);
    }

    static QDate* transformFromPython(PyObject* obj)
    {
        if (isPythonConvertible(obj)) {
            int day = PyDateTime_GET_DAY(obj);
            int month = PyDateTime_GET_MONTH(obj);
            int year = PyDateTime_GET_YEAR(obj);
            return new QDate(year, month, day);
        }
        return 0;
    }

    static PyObject* transformToPython(QDate* d)
    {
        if (d) {
            if (!PyDateTimeAPI) 
                PyDateTime_IMPORT;

            return PyDate_FromDate(d->year(), d->month(), d->day());
        }
        return 0;
    }
};
}

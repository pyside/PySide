#ifndef __QEASINGCURVE_GLUE__
#define __QEASINGCURVE_GLUE__ 

#include <Python.h>
#include <QEasingCurve>

class PySideEasingCurveFunctor
{
    public:
        static void init();
        static QEasingCurve::EasingFunction createCustomFuntion(PyObject* parent, PyObject* pyFunc);

        qreal operator()(qreal progress);

        PyObject* callable(); //Return New reference 
        static PyObject* callable(PyObject* parent); //Return New reference 

        ~PySideEasingCurveFunctor();
    private:
        PyObject* m_parent;
        PyObject* m_func;
        int m_index;

        PySideEasingCurveFunctor(int index, PyObject* parent, PyObject *pyFunc);
};

#endif

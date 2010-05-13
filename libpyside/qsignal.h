#ifndef QSIGNAL_H
#define QSIGNAL_H

#include <pysidemacros.h>
#include <Python.h>
#include <QObject>

namespace PySide
{

typedef struct {
    PyObject_HEAD
    bool initialized;
    char *signal_name;
    char **signatures;
    int signatures_size;
    PyObject *source;
} SignalData;

extern "C"
{
    PyAPI_DATA(PyTypeObject) PySideSignal_Type;
    PyAPI_DATA(PyTypeObject) PySideSignalInstance_Type;
}; //extern "C"

PYSIDE_API void signal_update_source(PyObject *source);

} //namespace PySide
#endif

#ifndef PYSIDE_SIGNAL_H
#define PYSIDE_SIGNAL_H

#include <pysidemacros.h>
#include <Python.h>
#include <QObject>

namespace PySide
{

typedef struct {
    PyObject_HEAD
    char* signalName;
    char* signature;
    PyObject* source;
    PyObject* next;
} SignalInstanceData;


extern "C"
{
    PyAPI_DATA(PyTypeObject) Signal_Type;
    PyAPI_DATA(PyTypeObject) SignalInstance_Type;
    PYSIDE_API PyAPI_FUNC(PyObject*) signal_new(const char* name, ...);
}; //extern "C"

PYSIDE_API void signal_update_source(PyObject* source);

} //namespace PySide

#endif

/*
* This file is part of the Shiboken Python Bindings Generator project.
*
* Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
*
* Contact: PySide team <contact@pyside.org>
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public License
* version 2.1 as published by the Free Software Foundation. Please
* review the following information to ensure the GNU Lesser General
* Public License version 2.1 requirements will be met:
* http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
*
* As a special exception to the GNU Lesser General Public License
* version 2.1, the object code form of a "work that uses the Library"
* may incorporate material from a header file that is part of the
* Library.  You may distribute such object code under terms of your
* choice, provided that the incorporated material (i) does not exceed
* more than 5% of the total size of the Library; and (ii) is limited to
* numerical parameters, data structure layouts, accessors, macros,
* inline functions and templates.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
* 02110-1301 USA
*/

#ifndef PYSIDECONVERSIONS_H
#define PYSIDECONVERSIONS_H

#include <Python.h>
#include <conversions.h>

template <typename QtDict>
struct QtDictConverter
{
    static inline bool checkType(PyObject* pyObj)
    {
        return isConvertible(pyObj);
    }

    static inline bool isConvertible(PyObject* pyObj)
    {
        if (PyObject_TypeCheck(pyObj, Shiboken::SbkType<QtDict>()))
            return true;

        if ((Shiboken::SbkType<QtDict>() && Shiboken::isShibokenType(pyObj)) || !PyDict_Check(pyObj))
            return false;

        PyObject* key;
        PyObject* value;
        Py_ssize_t pos = 0;

        while (PyDict_Next(pyObj, &pos, &key, &value)) {
            if (!Shiboken::Converter<typename QtDict::key_type>::isConvertible(key)
                && !Shiboken::Converter<typename QtDict::mapped_type>::isConvertible(value)) {
                return false;
            }
        }
        return true;
    }

    static inline PyObject* toPython(void* cppObj) { return toPython(*reinterpret_cast<QtDict*>(cppObj)); }
    static inline PyObject* toPython(const QtDict& cppobj)
    {
        PyObject* result = PyDict_New();
        typename QtDict::const_iterator it = cppobj.begin();

        for (; it != cppobj.end(); ++it) {
            Shiboken::AutoDecRef keyObj(Shiboken::Converter<typename QtDict::key_type>::toPython(it.key()));
            Shiboken::AutoDecRef valueObj(Shiboken::Converter<typename QtDict::mapped_type>::toPython(it.value()));
            PyDict_SetItem(result, keyObj, valueObj);
        }

        return result;
    }
    static inline QtDict toCpp(PyObject* pyobj)
    {
        if (PyObject_TypeCheck(pyobj, Shiboken::SbkType<QtDict>()))
            return *reinterpret_cast<QtDict*>(Shiboken::getCppPointer(pyobj, Shiboken::SbkType<QtDict>()));

        QtDict result;

        PyObject* key;
        PyObject* value;
        Py_ssize_t pos = 0;

        while (PyDict_Next(pyobj, &pos, &key, &value))
            result[Shiboken::Converter<typename QtDict::key_type>::toCpp(key)] = Shiboken::Converter<typename QtDict::mapped_type>::toCpp(value);
        return result;
    }
};

template <typename MultiMap>
struct QtMultiMapConverter
{
    static inline bool checkType(PyObject* pyObj)
    {
        return isConvertible(pyObj);
    }

    static inline bool isConvertible(PyObject* pyObj)
    {
        if (PyObject_TypeCheck(pyObj, Shiboken::SbkType<MultiMap>()))
            return true;

        if ((Shiboken::SbkType<MultiMap>() && Shiboken::isShibokenType(pyObj)) || !PyDict_Check(pyObj))
            return false;

        PyObject* key;
        PyObject* value;
        Py_ssize_t pos = 0;

        while (PyDict_Next(pyObj, &pos, &key, &value)) {
            if (!Shiboken::Converter<typename MultiMap::key_type>::isConvertible(key)) {
                if (PySequence_Check(value)) {
                    for (int i = 0, max = PySequence_Length(value); i < max; ++i) {
                        Shiboken::AutoDecRef item(PySequence_GetItem(value, i));
                        if (!Shiboken::Converter<typename MultiMap::mapped_type>::isConvertible(value))
                            return false;
                    }
                } else if (!Shiboken::Converter<typename MultiMap::mapped_type>::isConvertible(value)) {
                    return false;
                }
            }
        }
        return true;
    }

    static inline PyObject* toPython(void* cppObj) { return toPython(*reinterpret_cast<MultiMap*>(cppObj)); }
    static inline PyObject* toPython(const MultiMap& cppObj)
    {
        PyObject* result = PyDict_New();
        typename MultiMap::const_iterator it = cppObj.begin();

        for (; it != cppObj.end(); ++it) {
            Shiboken::AutoDecRef key(Shiboken::Converter<typename MultiMap::key_type>::toPython(it.key()));
            Shiboken::AutoDecRef value(Shiboken::Converter<typename MultiMap::mapped_type>::toPython(it.value()));

            PyObject* values = PyDict_GetItem(result, key);
            bool decRefValues = !values;
            if (!values)
                values = PyList_New(0);
            PyList_Append(values, value);
            PyDict_SetItem(result, key, values);
            if (decRefValues) {
                Py_DECREF(values);
            }
        }

        return result;
    }

    static inline MultiMap toCpp(PyObject* pyObj)
    {
        if (PyObject_TypeCheck(pyObj, Shiboken::SbkType<MultiMap>()))
            return *reinterpret_cast<MultiMap*>(Shiboken::getCppPointer(pyObj, Shiboken::SbkType<MultiMap>()));

        MultiMap result;

        PyObject* key;
        PyObject* value;
        Py_ssize_t pos = 0;

        while (PyDict_Next(pyObj, &pos, &key, &value))
            result[Shiboken::Converter<typename MultiMap::key_type>::toCpp(key)] = Shiboken::Converter<typename MultiMap::mapped_type>::toCpp(value);
        return result;
    }
};

template <typename T>
struct QSequenceConverter
{
    static inline bool checkType(PyObject* pyObj)
    {
        return isConvertible(pyObj);
    }

    static inline bool isConvertible(PyObject* pyObj)
    {
        if (PyObject_TypeCheck(pyObj, Shiboken::SbkType<T>()))
            return true;
        if ((Shiboken::SbkType<T>() && Shiboken::isShibokenType(pyObj)) || !PySequence_Check(pyObj))
            return false;
        for (int i = 0, max = PySequence_Length(pyObj); i < max; ++i) {
            Shiboken::AutoDecRef item(PySequence_GetItem(pyObj, i));
            if (!Shiboken::Converter<typename T::value_type>::isConvertible(item))
                return false;
        }
        return true;
    }
    static inline PyObject* toPython(void* cppObj) { return toPython(*reinterpret_cast<T*>(cppObj)); }
    static PyObject* toPython(const T& cppobj)
    {
        PyObject* result = PyList_New((int) cppobj.size());
        typename T::const_iterator it = cppobj.begin();
        for (int idx = 0; it != cppobj.end(); ++it, ++idx) {
            typename T::value_type vh(*it);
            PyList_SET_ITEM(result, idx, Shiboken::Converter<typename T::value_type>::toPython(vh));
        }
        return result;
    }
    static T toCpp(PyObject* pyobj)
    {
        if (PyObject_TypeCheck(pyobj, Shiboken::SbkType<T>()))
            return *reinterpret_cast<T*>(Shiboken::getCppPointer(pyobj, Shiboken::SbkType<T>()));

        Shiboken::AutoDecRef fastSequence(PySequence_Fast(pyobj, "Invalid sequence object"));
        T result;
        for (int i = 0; i < PySequence_Size(pyobj); i++) {
            PyObject* pyItem = PySequence_Fast_GET_ITEM(fastSequence.object(), i);
            result << Shiboken::Converter<typename T::value_type>::toCpp(pyItem);
        }
        return result;
    }
};

#endif

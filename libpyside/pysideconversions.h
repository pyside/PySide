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

template <typename StdMap>
struct QtDictConverter
{
    static inline bool checkType(PyObject* pyObj)
    {
        if (!PyDict_Check(pyObj))
            return false;

        PyObject* key;
        PyObject* value;
        Py_ssize_t pos = 0;

        while (PyDict_Next(pyObj, &pos, &key, &value)) {
            if (!Shiboken::Converter<typename StdMap::key_type>::checkType(key)
                && !Shiboken::Converter<typename StdMap::mapped_type>::checkType(value)
                && !Shiboken::Converter<typename StdMap::key_type>::isConvertible(key)
                && !Shiboken::Converter<typename StdMap::mapped_type>::isConvertible(value)) {
                return false;
            }
        }
        return true;
    }

    static inline bool isConvertible(PyObject* pyObj)
    {
        return checkType(pyObj);
    }

    static inline PyObject* toPython(const StdMap& cppobj)
    {
        PyObject* result = PyDict_New();
        typename StdMap::const_iterator it = cppobj.begin();

        for (; it != cppobj.end(); ++it) {
            PyDict_SetItem(result,
                           Shiboken::Converter<typename StdMap::key_type>::toPython(it.key()),
                           Shiboken::Converter<typename StdMap::mapped_type>::toPython(it.value()));
        }

        return result;
    }
    static inline StdMap toCpp(PyObject* pyobj)
    {
        StdMap result;

        PyObject* key;
        PyObject* value;
        Py_ssize_t pos = 0;

        while (PyDict_Next(pyobj, &pos, &key, &value))
            result[Shiboken::Converter<typename StdMap::key_type>::toCpp(key)] = Shiboken::Converter<typename StdMap::mapped_type>::toCpp(value);
        return result;
    }
};

#endif

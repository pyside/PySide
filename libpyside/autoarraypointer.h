/*
 * This file is part of the PySide project.
 *
 * Copyright (C) 2009-2010 Nokia Corporation and/or its subsidiary(-ies).
 *
 * Contact: PySide team <contact@pyside.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef AUTOARRAYPOINTER_H
#define AUTOARRAYPOINTER_H


namespace PySide
{

template<class T>
class AutoArrayPointer
{
    public:
        AutoArrayPointer(int size) { data = new T[size]; }
        T& operator[](int pos) { return data[pos]; }
        operator T*() const { return data; }
        ~AutoArrayPointer() { delete[] data; }
    private:
        T* data;
};

} //namespace PySide


#endif // AUTOARRAYPOINTER_H


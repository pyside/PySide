/*
 * This file is part of the PySide project.
 *
 * Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef DYNAMICMETAPROPERTY_P_H
#define DYNAMICMETAPROPERTY_P_H

#include <Python.h>
#include <QByteArray>
#include <QSharedPointer>

#define PYSIDE_SLOT_LIST_ATTR "_slots"

struct PySideProperty;
namespace PySide
{
    class MethodData
    {
    public:
        MethodData(){}
        MethodData(const char* signature, const char* type = 0);
        void clear();
        bool isValid() const;
        QByteArray signature() const;
        QByteArray type() const;
        bool operator==(const MethodData& other) const;
        bool operator==(const char* other) const;
        operator const char*() { return m_signature->data(); }

    private:
        QSharedPointer<QByteArray> m_signature;
        QSharedPointer<QByteArray> m_type;
    };

    class PropertyData
    {
    public:
        PropertyData();
        PropertyData(const char* name, int notifyId=0, PySideProperty* data = 0);
        QByteArray name() const;
        QByteArray type() const;
        uint flags() const;
        bool isValid() const;
        int notifyId() const;
        bool operator==(const PropertyData& other) const;
        bool operator==(const char* name) const;

    private:
        QByteArray m_name;
        int m_notifyId;
        PySideProperty* m_data;
    };
}

#endif

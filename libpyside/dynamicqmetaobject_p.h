/*
 * This file is part of the PySide project.
 *
 * Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
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

#include <sbkpython.h>
#include <QByteArray>
#include <QMetaMethod>

#define GLOBAL_RECEIVER_CLASS_NAME "__GlobalReceiver__"

struct PySideProperty;
namespace PySide
{
    class MethodData
    {
    public:
        MethodData();
        /**
         * \param signature method signature
         * \param type method return type
         */
        MethodData(QMetaMethod::MethodType mtype, const char* signature, const char* type = 0);
        void clear();
        bool isValid() const;
        const QByteArray& signature() const { return m_signature; }
        const QByteArray& type() const { return m_type; }
        QMetaMethod::MethodType methodType() const;
        bool operator==(const MethodData& other) const;

    private:
        QByteArray m_signature;
        QByteArray m_type;
        QMetaMethod::MethodType m_mtype;
        static const QByteArray m_emptySig;
    };

    class PropertyData
    {
    public:
        PropertyData();
        PropertyData(const char* name, int notifyId=0, PySideProperty* data = 0);
        const QByteArray& name() const { return m_name; }
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

inline bool MethodData::operator==(const MethodData& other) const
{
    return m_mtype == other.methodType() && m_signature == other.signature();
}

}

#endif

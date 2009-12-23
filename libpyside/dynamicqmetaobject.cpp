/*
* This file is part of the Shiboken Python Bindings Generator project.
*
* Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
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

#include "dynamicqmetaobject.h"
#include <QByteArray>
#include <QString>
#include <QList>
#include <QObject>
#include <cstring>
#include <QDebug>

using namespace PySide;

static int registerString(const QByteArray& s, QList<QByteArray>* strings)
{
    int idx = 0;
    for (int i = 0; i < strings->count(); ++i) {
        const QString &str = strings->at(i);
        if (str == s)
            return idx;
        idx += str.length() + 1;
    }
    strings->append(s);
    return idx;
}

DynamicQMetaObject::DynamicQMetaObject(const QMetaObject* metaObject)
{
    d.superdata = metaObject;
    d.stringdata = 0;
    d.data = 0;
    d.extradata = 0;
    updateMetaObject();
}

DynamicQMetaObject::~DynamicQMetaObject()
{
    delete[] d.stringdata;
    delete[] d.data;
}

void DynamicQMetaObject::addSignal(const char* signal)
{
    m_signals << QByteArray(signal);
    updateMetaObject();
}

void DynamicQMetaObject::addSlot(const char* slot)
{
    m_slots << QByteArray(slot);
    updateMetaObject();
}

void DynamicQMetaObject::updateMetaObject()
{
    // these values are from moc source code, generator.cpp:66
    enum MethodFlags {
        AccessPrivate = 0x00,
        AccessProtected = 0x01,
        AccessPublic = 0x02,
        MethodMethod = 0x00,
        MethodSignal = 0x04,
        MethodSlot = 0x08,
        MethodConstructor = 0x0c,
        MethodCompatibility = 0x10,
        MethodCloned = 0x20,
        MethodScriptable = 0x40
    };

    uint n_signals = m_signals.count();
    uint n_methods = n_signals + m_slots.count();
    int header[] = {2,            // revision
    0,            // class name index in m_metadata
    0, 0,         // classinfo and classinfo index, not used by us
    n_methods, 0, // method count and method list index
    0, 0,         // prop count and prop indexes
    0, 0          // enum count and enum index
    };

    const int HEADER_LENGHT = sizeof(header)/sizeof(int);
    header[5] = HEADER_LENGHT;
    // header size + 5 indexes per method + an ending zero
    delete[] d.data;
    unsigned int* data;
    data = new unsigned int[HEADER_LENGHT + n_methods*5 + 1];
    std::memcpy(data, header, sizeof(header));

    QList<QByteArray> strings;
    registerString(d.superdata->className(), &strings); // register class string
    const int NULL_INDEX = registerString("", &strings); // register a null string
    int index = HEADER_LENGHT;

    //write signals
    foreach(QByteArray signal, m_signals) {
        data[index++] = registerString(signal, &strings); // func name
        data[index++] = NULL_INDEX; // arguments
        data[index++] = NULL_INDEX; // normalized type
        data[index++] = NULL_INDEX; // tags
        data[index++] = AccessPublic | MethodSignal; // flags
    }
    //write slots
    foreach(QByteArray slot, m_slots) {
        data[index++] = registerString(slot, &strings); // func name
        data[index++] = NULL_INDEX; // arguments
        data[index++] = NULL_INDEX; // normalized type
        data[index++] = NULL_INDEX; // tags
        data[index++] = AccessPublic | MethodSlot; // flags
    }
    data[index++] = 0; // the end

    // create the m_metadata string
    QByteArray str;
    foreach(QByteArray signature, strings) {
        str.append(signature);
        str.append(char(0));
    }
    delete[] d.stringdata;
    char* stringData = new char[str.count()];
    std::copy(str.begin(), str.end(), stringData);
    d.data = data;
    d.stringdata = stringData;
}

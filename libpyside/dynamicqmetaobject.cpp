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
#include <QStringList>
#include <QList>
#include <QObject>
#include <cstring>
#include <QDebug>
#include <QMetaMethod>

#include "qsignal.h"

#define MAX_SIGNALS_COUNT 50

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

MethodData::MethodData(const char* signature, const char* type)
{
    m_signature = QSharedPointer<QByteArray>(new QByteArray(signature));
    m_type = QSharedPointer<QByteArray>(new QByteArray(type));
}

void MethodData::clear()
{
    m_signature->clear();
    m_type->clear();
}

bool MethodData::operator==(const MethodData& other) const
{
    return *m_signature == other.signature();
}

bool MethodData::operator==(const char* other) const
{
    return *m_signature == other;
}

QByteArray MethodData::signature() const
{
    if (!m_signature.isNull())
        return *m_signature;
    else
        return QByteArray();
}

QByteArray MethodData::type() const
{
    if (!m_type.isNull()) {
        if (*m_type == "void")
            return QByteArray();
        return *m_type;
    } else {
        return QByteArray();
    }
}

bool MethodData::isValid() const
{
    return m_signature->size();
}

DynamicQMetaObject::DynamicQMetaObject(const char* className, const QMetaObject* metaObject)
{
    d.superdata = metaObject;
    d.stringdata = 0;
    d.data = 0;
    d.extradata = 0;
    m_className = QByteArray(className);
    updateMetaObject();
}

DynamicQMetaObject::~DynamicQMetaObject()
{
    delete[] d.stringdata;
    delete[] d.data;
}

void DynamicQMetaObject::addSignal(const char* signal, const char* type)
{
    QLinkedList<MethodData>::iterator i = qFind(m_signals.begin(), m_signals.end(), signal);
    if (i != m_signals.end())
        return;

    //search for a empty space
    MethodData blank;
    i = qFind(m_signals.begin(), m_signals.end(), blank);
    if (i != m_signals.end()) {
        *i = MethodData(signal, type);
        updateMetaObject();
        return;
    }

    if (m_signals.size() >= MAX_SIGNALS_COUNT) {
        qWarning() << "Fail to add dynamic signal to QObject. PySide support at most" << MAX_SIGNALS_COUNT << "dynamic signals.";
        return;
    }

    m_signals << MethodData(signal, type);
    updateMetaObject();
}

void DynamicQMetaObject::addSlot(const char* slot, const char* type)
{
    QLinkedList<MethodData>::iterator i = qFind(m_slots.begin(), m_slots.end(), slot);
    if (i != m_slots.end())
        return;

    //search for a empty space
    MethodData blank;
    i = qFind(m_slots.begin(), m_slots.end(), blank);
    if (i != m_slots.end()) {
        *i = MethodData(slot, type);
    } else {
        m_slots << MethodData(slot, type);
    }
    updateMetaObject();
}

void DynamicQMetaObject::removeSlot(uint index)
{
    QMetaMethod m = method(index);
    foreach(MethodData md, m_slots) {
        if (md.signature() == m.signature()) {
            md.clear();
            updateMetaObject();
            break;
        }
    }
}

DynamicQMetaObject* DynamicQMetaObject::createBasedOn(PyObject* pyObj, PyTypeObject* type, const QMetaObject* base)
{
    PyObject* key;
    PyObject* value;
    Py_ssize_t pos = 0;

    QString className(type->tp_name);
    className = className.mid(className.lastIndexOf('.')+1);
    DynamicQMetaObject *mo = new PySide::DynamicQMetaObject(className.toAscii(), base);

    while (PyDict_Next(type->tp_dict, &pos, &key, &value)) {

        //Register signals
        if (value->ob_type == &Signal_Type) {
            PyObject *attr = PyObject_GetAttr(pyObj, key);
            SignalInstanceData *data = reinterpret_cast<SignalInstanceData*>(attr);
            while(data) {
                mo->addSignal(data->signature);
                data = reinterpret_cast<SignalInstanceData*>(data->next);
            }
        }

        if (!PyFunction_Check(value))
            continue;

        //Register Slots
        if (PyObject_HasAttrString(value, PYSIDE_SLOT_LIST_ATTR)) {
            PyObject *signature_list = PyObject_GetAttrString(value, PYSIDE_SLOT_LIST_ATTR);
            for(Py_ssize_t i = 0, i_max = PyList_Size(signature_list); i < i_max; i++) {
                PyObject *signature = PyList_GET_ITEM(signature_list, i);
                QString sig(PyString_AsString(signature));
                //slot the slot type and signature
                QStringList slotInfo = sig.split(" ", QString::SkipEmptyParts);
                mo->addSlot(slotInfo[1].toAscii(), slotInfo[0].toAscii());
            }
        }
    }
    return mo;
}

void DynamicQMetaObject::removeSignal(uint index)
{
    //Current Qt implementation does not support runtime remove signal
    QMetaMethod m = method(index);
    foreach(MethodData md, m_signals) {
        if (md.signature() == m.signature()) {
            md.clear();
            updateMetaObject();
            break;
        }
    }
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

    uint n_signals = MAX_SIGNALS_COUNT;
    uint n_methods = n_signals + m_slots.count();
    int header[] = {5,            // revision
                    0,            // class name index in m_metadata
                    0, 0,         // classinfo and classinfo index, not used by us
                    n_methods, 0, // method count and method list index
                    0, 0,         // prop count and prop indexes
                    0, 0,         // enum count and enum index
                    0, 0,         // constructors
                    MAX_SIGNALS_COUNT};

    const int HEADER_LENGHT = sizeof(header)/sizeof(int);
    header[5] = HEADER_LENGHT;
    // header size + 5 indexes per method + an ending zero
    delete[] d.data;
    unsigned int* data;
    data = new unsigned int[HEADER_LENGHT + n_methods*5 + 1];
    std::memcpy(data, header, sizeof(header));

    QList<QByteArray> strings;
    registerString(m_className, &strings); // register class string
    const int NULL_INDEX = registerString("", &strings); // register a null string
    int index = HEADER_LENGHT;

    //write signals
    QLinkedList<MethodData>::iterator iSignal = m_signals.begin();
    for(int i=0; i < MAX_SIGNALS_COUNT; i++) {
        QByteArray sigType;
        if (iSignal != m_signals.end() && ((*iSignal).signature().size() > 0) ) {
            data[index++] = registerString((*iSignal).signature(), &strings); // func name
            sigType = (*iSignal).type();
            iSignal++;
        } else {
            data[index++] = NULL_INDEX; // func name
        }
        data[index++] = NULL_INDEX; // arguments
        data[index++] = (sigType.size() > 0 ? registerString(sigType, &strings) : NULL_INDEX); // normalized type
        data[index++] = NULL_INDEX; // tags
        data[index++] = AccessPublic | MethodSignal; // flags
    }


    //write slots
    foreach(MethodData slot, m_slots) {
        if (slot.isValid())
            data[index++] = registerString(slot.signature(), &strings); // func name
        else
            data[index++] = NULL_INDEX;

        data[index++] = NULL_INDEX; // arguments
        data[index++] = (slot.isValid() ? registerString(slot.type(), &strings) :  NULL_INDEX); // normalized type
        data[index++] = NULL_INDEX; // tags
        data[index++] = AccessPublic | MethodSlot; // flags
    }
    data[index++] = 0; // the end

    // create the m_metadata string
    QByteArray str;
    foreach(QByteArray field, strings) {
        str.append(field);
        str.append(char(0));
    }

    delete[] d.stringdata;
    char* stringData = new char[str.count()];
    std::copy(str.begin(), str.end(), stringData);
    d.data = data;
    d.stringdata = stringData;
}

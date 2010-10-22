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

#include "dynamicqmetaobject.h"
#include "dynamicqmetaobject_p.h"
#include <QByteArray>
#include <QString>
#include <QStringList>
#include <QList>
#include <QLinkedList>
#include <QObject>
#include <cstring>
#include <QDebug>
#include <QMetaMethod>

#include "qsignal.h"
#include "qsignal_p.h"
#include "qproperty.h"
#include "qproperty_p.h"

#define MAX_SIGNALS_COUNT 50
#define MAX_SLOTS_COUNT 50

#define MAX_GLOBAL_SIGNALS_COUNT 500
#define MAX_GLOBAL_SLOTS_COUNT 500

#define GLOBAL_RECEIVER_CLASS_NAME "__GlobalReceiver__"

using namespace PySide;

enum PropertyFlags  {
    Invalid = 0x00000000,
    Readable = 0x00000001,
    Writable = 0x00000002,
    Resettable = 0x00000004,
    EnumOrFlag = 0x00000008,
    StdCppSet = 0x00000100,
//     Override = 0x00000200,
    Constant = 0x00000400,
    Final = 0x00000800,
    Designable = 0x00001000,
    ResolveDesignable = 0x00002000,
    Scriptable = 0x00004000,
    ResolveScriptable = 0x00008000,
    Stored = 0x00010000,
    ResolveStored = 0x00020000,
    Editable = 0x00040000,
    ResolveEditable = 0x00080000,
    User = 0x00100000,
    ResolveUser = 0x00200000,
    Notify = 0x00400000
};

class DynamicQMetaObject::DynamicQMetaObjectPrivate
{
public:
    QList<MethodData> m_signals;
    QList<MethodData> m_slots;
    QList<PropertyData> m_properties;
    QByteArray m_className;

    void updateMetaObject(QMetaObject* metaObj);
    void writeMethodsData(QList<MethodData>& methods, unsigned int** data, QList<QByteArray>* strings, int* prtIndex, int maxCount, int nullIndex, int flags);
};

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

static int qvariant_nameToType(const char* name)
{
    if (!name)
        return 0;

    if (strcmp(name, "QVariant") == 0)
        return 0xffffffff;
    if (strcmp(name, "QCString") == 0)
        return QMetaType::QByteArray;
    if (strcmp(name, "Q_LLONG") == 0)
        return QMetaType::LongLong;
    if (strcmp(name, "Q_ULLONG") == 0)
        return QMetaType::ULongLong;
    if (strcmp(name, "QIconSet") == 0)
        return QMetaType::QIcon;

    uint tp = QMetaType::type(name);
    return tp < QMetaType::User ? tp : 0;
}

/*
  Returns true if the type is a QVariant types.
*/
static bool isVariantType(const char* type)
{
    return qvariant_nameToType(type) != 0;
}

/*!
  Returns true if the type is qreal.
*/
static bool isQRealType(const char *type)
{
    return strcmp(type, "qreal") == 0;
}



/*
 * Avoid API break keep this on cpp
 */
static int maxSlotsCount(const QString& className)
{
    int maxSlots = MAX_SLOTS_COUNT;
    if (className == GLOBAL_RECEIVER_CLASS_NAME)
        maxSlots = MAX_GLOBAL_SIGNALS_COUNT;
    return maxSlots;
}

static int maxSignalsCount(const QString& className)
{
    int maxSignals = MAX_SIGNALS_COUNT;
    if (className == GLOBAL_RECEIVER_CLASS_NAME)
        maxSignals = MAX_GLOBAL_SIGNALS_COUNT;
    return maxSignals;
}

uint PropertyData::flags() const
{
    const char* typeName = type().data();
    uint flags = Invalid;
    if (!isVariantType(typeName))
         flags |= EnumOrFlag;
    else if (!isQRealType(typeName))
        flags |= qvariant_nameToType(typeName) << 24;

    if (qpropertyIsReadable(m_data))
        flags |= Readable;

    if (qpropertyIsWritable(m_data))
        flags |= Writable;

    if (qpropertyHasReset(m_data))
        flags |= Resettable;

    if (!qpropertyIsDesignable(m_data))
        flags |= ResolveDesignable;
    else
        flags |= Designable;

    if (!qpropertyIsScriptable(m_data))
        flags |= ResolveScriptable;
    else
        flags |= Scriptable;

    if (!qpropertyIsStored(m_data))
        flags |= ResolveStored;
    else
        flags |= Stored;

    if (!qpropertyIsUser(m_data))
        flags |= ResolveUser;
    else
        flags |= User;

    if (qpropertyIsConstant(m_data))
        flags |= Constant;

    if (qpropertyIsFinal(m_data))
        flags |= Final;

    if (m_notifyId)
        flags |= Notify;

    return flags;
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

PropertyData::PropertyData()
    : m_notifyId(0), m_data(0)
{
}

PropertyData::PropertyData(const char* name, uint notifyId, PySideQProperty* data)
    : m_name(name), m_notifyId(notifyId), m_data(data)
{
}

QByteArray PropertyData::type() const
{
    return QByteArray(qpropertyGetType(m_data));
}


bool PropertyData::isValid() const
{
    return !m_name.isEmpty();
}

QByteArray PropertyData::name() const
{
    return m_name;
}

uint PropertyData::notifyId() const
{
    return m_notifyId;
}

bool PropertyData::operator==(const PropertyData& other) const
{
    return m_data == other.m_data;
}

bool PropertyData::operator==(const char* name) const
{
    return m_name == QString(name);
}


DynamicQMetaObject::DynamicQMetaObject(const char* className, const QMetaObject* metaObject) : m_d(new DynamicQMetaObjectPrivate)
{
    d.superdata = metaObject;
    d.stringdata = 0;
    d.data = 0;
    d.extradata = 0;
    m_d->m_className = QByteArray(className);
    m_d->updateMetaObject(this);
}

DynamicQMetaObject::~DynamicQMetaObject()
{
    delete[] d.stringdata;
    delete[] d.data;
    delete m_d;
}

void DynamicQMetaObject::addSignal(const char* signal, const char* type)
{
    int index = m_d->m_signals.indexOf(signal);
    if (index != -1)
        return;

    //search for a empty space
    MethodData blank;
    index = m_d->m_signals.indexOf(blank);
    if (index != -1) {
        m_d->m_signals[index] = MethodData(signal, type);
        m_d->updateMetaObject(this);
        return;
    }

    int maxSignals = maxSignalsCount(m_d->m_className);
    if (m_d->m_signals.size() >= maxSignals) {
        qWarning() << "Fail to add dynamic signal to QObject. PySide support at most" << maxSignals << "dynamic signals.";
        return;
    }

    m_d->m_signals << MethodData(signal, type);
    m_d->updateMetaObject(this);
}

void DynamicQMetaObject::addSlot(const char* slot, const char* type)
{
    int index = m_d->m_slots.indexOf(slot);
    if (index != -1)
        return;

    int maxSlots = maxSlotsCount(m_d->m_className);
    if (m_d->m_slots.size() >= maxSlots) {
        qWarning() << "Fail to add dynamic slot to QObject. PySide support at most" << maxSlots << "dynamic slots.";
        return;
    }

    //search for a empty space
    MethodData blank;
    index = m_d->m_slots.indexOf(blank);
    if (index != -1) {
        m_d->m_slots[index] = MethodData(slot, type);
    } else {
        m_d->m_slots << MethodData(slot, type);
    }
    m_d->updateMetaObject(this);
}

void DynamicQMetaObject::removeSlot(uint index)
{
    QMetaMethod m = method(index);
    foreach(MethodData md, m_d->m_slots) {
        if (md.signature() == m.signature()) {
            md.clear();
            m_d->updateMetaObject(this);
            break;
        }
    }
}

void DynamicQMetaObject::addProperty(const char* propertyName, PyObject* data)
{
    int index = m_d->m_properties.indexOf(propertyName);
    if (index != -1)
        return;

    // retrieve notifyId
    PySideQProperty* property = reinterpret_cast<PySideQProperty*>(data);
    const char* signalNotify = qpropertyGetNotify(property);
    uint notifyId = 0;
    if (signalNotify) {
        QByteArray signalSignature(signalNotify);
        notifyId = m_d->m_signals.indexOf(signalNotify) + 1;
    }

    //search for a empty space
    PropertyData blank;
    index = m_d->m_properties.indexOf(blank);
    if (index != -1) {
        m_d->m_properties[index] = PropertyData(propertyName, notifyId, property);
    } else {
        m_d->m_properties << PropertyData(propertyName, notifyId, property);
    }
    m_d->updateMetaObject(this);
}


DynamicQMetaObject* DynamicQMetaObject::createBasedOn(PyObject* pyObj, PyTypeObject* type, const QMetaObject* base)
{
    PyObject* key;
    PyObject* value;
    Py_ssize_t pos = 0;

    QString className(type->tp_name);
    className = className.mid(className.lastIndexOf('.')+1);
    DynamicQMetaObject *mo = new PySide::DynamicQMetaObject(className.toAscii(), base);

    QList<PyObject*> properties;

    while (PyDict_Next(type->tp_dict, &pos, &key, &value)) {

        //Leave the properties to be register after signals because of notify object
        if (value->ob_type == &PySideQPropertyType)
            properties.append(key);

        //Register signals
        if (value->ob_type == &PySideSignalType) {
            PyObject *attr = PyObject_GetAttr(pyObj, key);
            PySideSignalInstanceData *data = reinterpret_cast<PySideSignalInstanceData*>(attr);
            while(data) {
                int index = base->indexOfSignal(data->d->signature);
                if (index == -1)
                    mo->addSignal(data->d->signature);
                data = reinterpret_cast<PySideSignalInstanceData*>(data->d->next);
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
                int index = base->indexOfSlot(slotInfo[0].toAscii());
                if (index == -1)
                    mo->addSlot(slotInfo[1].toAscii(), slotInfo[0].toAscii());
            }
        }
    }

    //Register properties
    foreach(PyObject* key, properties) {
        PyObject* value = PyDict_GetItem(type->tp_dict, key);
        mo->addProperty(PyString_AsString(key), value);
    }

    return mo;
}

void DynamicQMetaObject::removeSignal(uint index)
{
    //Current Qt implementation does not support runtime remove signal
    QMetaMethod m = method(index);
    foreach(MethodData md, m_d->m_signals) {
        if (md.signature() == m.signature()) {
            md.clear();
            m_d->updateMetaObject(this);
            break;
        }
    }
}

void DynamicQMetaObject::DynamicQMetaObjectPrivate::writeMethodsData(QList<MethodData>& methods,
                                                                     unsigned int** data,
                                                                     QList<QByteArray>* strings,
                                                                     int* prtIndex,
                                                                     int maxCount,
                                                                     int nullIndex,
                                                                     int flags)
{
    int index = *prtIndex;

    QList<MethodData>::iterator iMethod = methods.begin();
    for(int i=0; i < maxCount; i++) {
        QByteArray mType;
        if (iMethod != methods.end() && ((*iMethod).signature().size() > 0) ) {
            (*data)[index++] = registerString((*iMethod).signature(), strings); // func name
            mType = (*iMethod).type();
        } else {
            (*data)[index++] = nullIndex; // func name
        }
        (*data)[index++] = nullIndex; // arguments
        (*data)[index++] = (mType.size() > 0 ? registerString(mType, strings) : nullIndex); // normalized type
        (*data)[index++] = nullIndex; // tags
        (*data)[index++] = flags;
        if (iMethod != methods.end())
            iMethod++;
    }

    *prtIndex = index;
}

void DynamicQMetaObject::DynamicQMetaObjectPrivate::updateMetaObject(QMetaObject* metaObj)
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

    int maxSignals = maxSignalsCount(m_className);
    int maxSlots = maxSlotsCount(m_className);

    uint n_signals = maxSignals;
    uint n_methods = n_signals + maxSlots;
    uint n_properties = m_properties.size();
    int header[] = {5,            // revision
                    0,            // class name index in m_metadata
                    0, 0,         // classinfo and classinfo index, not used by us
                    n_methods, 0, // method count and method list index
                    n_properties, 0, // prop count and prop indexes
                    0, 0,         // enum count and enum index
                    0, 0,         // constructors
                    n_signals};

    const int HEADER_LENGHT = sizeof(header)/sizeof(int);
    header[5] = HEADER_LENGHT;
    // header size + 5 indexes per method + an ending zero
    delete[] metaObj->d.data;
    unsigned int* data;
    data = new unsigned int[HEADER_LENGHT + n_methods*5 + n_properties*4 + 1];
    std::memcpy(data, header, sizeof(header));

    QList<QByteArray> strings;
    registerString(m_className, &strings); // register class string
    const int NULL_INDEX = registerString("", &strings); // register a null string
    int index = HEADER_LENGHT;

    //write signals
    writeMethodsData(m_signals, &data, &strings, &index, maxSignals, NULL_INDEX, AccessPublic | MethodSignal);

    //write slots
    writeMethodsData(m_slots, &data, &strings, &index, maxSlots, NULL_INDEX, AccessPublic | MethodSlot);

    if (m_properties.size())
        data[7] = index;

    //write properties
    foreach(PropertyData pp, m_properties) {
        if (pp.isValid())
            data[index++] = registerString(pp.name(), &strings); // name
        else
            data[index++] = NULL_INDEX;

        data[index++] = (pp.isValid() ? registerString(pp.type(), &strings) :  NULL_INDEX); // normalized type
        data[index++] = pp.flags();
    }

    //write properties notify
    foreach(PropertyData pp, m_properties) {
        data[index++] = pp.notifyId(); //signal notify index
    }

    data[index++] = 0; // the end

    // create the m_metadata string
    QByteArray str;
    foreach(QByteArray field, strings) {
        str.append(field);
        str.append(char(0));
    }

    delete[] metaObj->d.stringdata;
    char* stringData = new char[str.count()];
    std::copy(str.begin(), str.end(), stringData);
    metaObj->d.data = data;
    metaObj->d.stringdata = stringData;
}

void PySide::deleteDynamicQMetaObject(void* data)
{
    delete reinterpret_cast<DynamicQMetaObject*>(data);
}

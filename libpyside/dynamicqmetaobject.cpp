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
#include "pysidesignal.h"
#include "pysidesignal_p.h"
#include "pysideproperty.h"
#include "pysideproperty_p.h"
#include "pysideslot_p.h"

#include <QByteArray>
#include <QString>
#include <QStringList>
#include <QList>
#include <QLinkedList>
#include <QObject>
#include <cstring>
#include <QDebug>
#include <QMetaMethod>
#include <shiboken.h>

#define EMPTY_META_METHOD "0()"

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

class DynamicQMetaObject::DynamicQMetaObjectPrivate
{
public:
    QList<MethodData> m_methods;
    QList<PropertyData> m_properties;

    // methods added/remove not writed on metadata yet
    int m_lastMethod;
    int m_lastProperty;
    int m_lastInfo;

    QMap<QByteArray, QByteArray> m_info;
    QByteArray m_className;
    bool m_updated; // when the meta data is not update
    bool m_invalid; // when the object need to be reconstructed
    int m_methodOffset;
    int m_propertyOffset;
    int m_count;
    int m_dataSize;
    int m_stringDataSize;
    int m_emptyMethod;
    int m_nullIndex;

    DynamicQMetaObjectPrivate()
        : m_lastMethod(0), m_lastProperty(0), m_lastInfo(0),
          m_updated(false), m_invalid(true), m_methodOffset(0), m_propertyOffset(0),
          m_count(0), m_dataSize(0), m_stringDataSize(0), m_emptyMethod(-1), m_nullIndex(0) {}

    int createMetaData(QMetaObject* metaObj, QLinkedList<QByteArray> &strings);
    void updateMetaObject(QMetaObject* metaObj);
    void writeMethodsData(const QList<MethodData>& methods, unsigned int** data, QLinkedList<QByteArray>& strings, int* prtIndex, int nullIndex, int flags);
};

static int registerString(const QByteArray& s, QLinkedList<QByteArray>& strings)
{
    int idx = 0;
    QLinkedList<QByteArray>::const_iterator it = strings.begin();
    QLinkedList<QByteArray>::const_iterator itEnd = strings.end();
    while (it != itEnd) {
        if (strcmp(*it, s) == 0)
            return idx;
        idx += it->size() + 1;
        ++it;
    }
    strings.append(s);
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

uint PropertyData::flags() const
{
    const char* typeName = type().data();
    uint flags = Invalid;
    if (!isVariantType(typeName))
         flags |= EnumOrFlag;
    else if (!isQRealType(typeName))
        flags |= qvariant_nameToType(typeName) << 24;

    if (PySide::Property::isReadable(m_data))
        flags |= Readable;

    if (PySide::Property::isWritable(m_data))
        flags |= Writable;

    if (PySide::Property::hasReset(m_data))
        flags |= Resettable;

    if (PySide::Property::isDesignable(m_data))
        flags |= Designable;
    else
        flags |= ResolveDesignable;

    if (PySide::Property::isScriptable(m_data))
        flags |= Scriptable;
    else
        flags |= ResolveScriptable;

    if (PySide::Property::isStored(m_data))
        flags |= Stored;
    else
        flags |= ResolveStored;

    //EDITABLE
    flags |= ResolveEditable;

    if (PySide::Property::isUser(m_data))
        flags |= User;
    else
        flags |= ResolveUser;

    if (m_notifyId != -1)
        flags |= Notify;

    if (PySide::Property::isConstant(m_data))
        flags |= Constant;

    if (PySide::Property::isFinal(m_data))
        flags |= Final;

    return flags;
}

// const QByteArray with EMPTY_META_METHOD, used to save some memory
const QByteArray MethodData::m_emptySig(EMPTY_META_METHOD);

MethodData::MethodData()
    : m_signature(m_emptySig)
{
}

MethodData::MethodData(QMetaMethod::MethodType mtype, const char* signature, const char* type)
    : m_signature(signature), m_mtype(mtype)
{
    if (qstrcmp(type, "void"))
        m_type = type;
}

void MethodData::clear()
{
    m_signature = m_emptySig;
    m_type.clear();
}

bool MethodData::isValid() const
{
    return m_signature != m_emptySig;
}

QMetaMethod::MethodType MethodData::methodType() const
{
    return m_mtype;
}

PropertyData::PropertyData()
    : m_notifyId(0), m_data(0)
{
}

PropertyData::PropertyData(const char* name, int notifyId, PySideProperty* data)
    : m_name(name), m_notifyId(notifyId), m_data(data)
{
}

QByteArray PropertyData::type() const
{
    return QByteArray(PySide::Property::getTypeName(m_data));
}


bool PropertyData::isValid() const
{
    return !m_name.isEmpty();
}

int PropertyData::notifyId() const
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


DynamicQMetaObject::DynamicQMetaObject(PyTypeObject* type, const QMetaObject* base)
    : m_d(new DynamicQMetaObjectPrivate)
{
    d.superdata = base;
    d.stringdata = NULL;
    d.data = NULL;
    d.extradata = NULL;

    m_d->m_className = QByteArray(type->tp_name).split('.').last();
    m_d->m_methodOffset = base->methodCount() - 1;
    m_d->m_propertyOffset = base->propertyCount() - 1;
    parsePythonType(type);
}

DynamicQMetaObject::DynamicQMetaObject(const char* className, const QMetaObject* metaObject)
    : m_d(new DynamicQMetaObjectPrivate)
{
    d.superdata = metaObject;
    d.stringdata = 0;
    d.data = 0;
    d.extradata = 0;
    m_d->m_className = className;
    m_d->m_methodOffset = metaObject->methodCount() - 1;
    m_d->m_propertyOffset = metaObject->propertyCount() - 1;
}

DynamicQMetaObject::~DynamicQMetaObject()
{
    free(const_cast<char*>(d.stringdata));
    free(const_cast<uint*>(d.data));
    delete m_d;
}

int DynamicQMetaObject::addMethod(QMetaMethod::MethodType mtype, const char* signature, const char* type)
{
    int index = -1;
    int counter = 0;

    QList<MethodData>::iterator it = m_d->m_methods.begin();
    for (; it != m_d->m_methods.end(); ++it) {
        if ((it->signature() == signature) && (it->methodType() == mtype))
            return m_d->m_methodOffset + counter;
        else if (!it->isValid()) {
            index = counter;
            m_d->m_invalid = true; // need rewrite all methods again
        }
        counter++;
    }

    //has blank method
    if (index != -1) {
        m_d->m_methods[index] = MethodData(mtype, signature, type);
        index++;
    } else {
        m_d->m_methods << MethodData(mtype, signature, type);
        index = m_d->m_methods.size();
    }

    m_d->m_updated = false;
    return m_d->m_methodOffset + index;
}

void DynamicQMetaObject::removeMethod(QMetaMethod::MethodType mtype, uint index)
{
    const char* methodSig = method(index).signature();
    QList<MethodData>::iterator it = m_d->m_methods.begin();
    for (; it != m_d->m_methods.end(); ++it) {
        if ((it->signature() == methodSig) && (it->methodType() == mtype)){
            it->clear();
            m_d->m_invalid = true;
            break;
        }
    }
}

int DynamicQMetaObject::addSignal(const char* signal, const char* type)
{
    return addMethod(QMetaMethod::Signal, signal, type);
}

int DynamicQMetaObject::addSlot(const char* slot, const char* type)
{
    return addMethod(QMetaMethod::Slot, slot, type);
}

void DynamicQMetaObject::removeSlot(uint index)
{
    removeMethod(QMetaMethod::Slot, index);
}

void DynamicQMetaObject::removeSignal(uint index)
{
    removeMethod(QMetaMethod::Signal, index);
}

int DynamicQMetaObject::addProperty(const char* propertyName, PyObject* data)
{
    int index = m_d->m_properties.indexOf(propertyName);
    if (index != -1)
        return m_d->m_propertyOffset + index;

    // retrieve notifyId
    int notifyId = -1;
    PySideProperty* property = reinterpret_cast<PySideProperty*>(data);
    if (property->d->notify) {
        const char* signalNotify = PySide::Property::getNotifyName(property);
        if (signalNotify) {
            MethodData signalObject(QMetaMethod::Signal, signalNotify, "");
            notifyId = m_d->m_methods.indexOf(signalObject);
        }
    }

    //search for a empty space
    PropertyData blank;
    index = m_d->m_properties.indexOf(blank);
    if (index != -1) {
        m_d->m_properties[index] = PropertyData(propertyName, notifyId, property);
        m_d->m_invalid = true;
    } else {
        m_d->m_properties << PropertyData(propertyName, notifyId, property);
        index = m_d->m_properties.size();
    }
    m_d->m_updated = false;
    return  m_d->m_propertyOffset + index;
}

void DynamicQMetaObject::addInfo(const char* key, const char* value)
{
    m_d->m_info[key] = value;
}

void DynamicQMetaObject::addInfo(QMap<QByteArray, QByteArray> info)
{
    QMap<QByteArray, QByteArray>::const_iterator i = info.constBegin();
    while (i != info.constEnd()) {
        m_d->m_info[i.key()] = i.value();
        ++i;
    }
    m_d->m_updated = false;
}

const QMetaObject* DynamicQMetaObject::update() const
{
    if (!m_d->m_updated || m_d->m_invalid) {
        m_d->updateMetaObject(const_cast<DynamicQMetaObject*>(this));
        m_d->m_updated = true;
    }
    return this;
}

void DynamicQMetaObject::DynamicQMetaObjectPrivate::writeMethodsData(const QList<MethodData>& methods,
                                                                     unsigned int** data,
                                                                     QLinkedList<QByteArray>& strings,
                                                                     int* prtIndex,
                                                                     int nullIndex,
                                                                     int flags)
{
    int index = *prtIndex;
    //skip to last registered method
    QList<MethodData>::const_iterator it = methods.begin() + m_lastMethod;

    if (m_emptyMethod == -1)
        m_emptyMethod = registerString(EMPTY_META_METHOD, strings) + m_stringDataSize;

    for (; it != methods.end(); ++it) {
        if (it->signature() != EMPTY_META_METHOD)
            (*data)[index++] = registerString(it->signature(), strings) + m_stringDataSize; // func name
        else
            (*data)[index++] = m_emptyMethod; // func name

        (*data)[index++] = nullIndex; // arguments
        (*data)[index++] = (it->type().size() > 0 ? registerString(it->type(), strings) : nullIndex); // normalized type
        (*data)[index++] = nullIndex; // tags
        (*data)[index++] = flags  |  (it->methodType() == QMetaMethod::Signal ? MethodSignal : MethodSlot);
    }
    *prtIndex = index;

    //update last registered method
    m_lastMethod = methods.size();
}

void DynamicQMetaObject::parsePythonType(PyTypeObject* type)
{
    PyObject* attrs = type->tp_dict;
    PyObject* key = 0;
    PyObject* value = 0;
    Py_ssize_t pos = 0;

    typedef std::pair<const char*, PyObject*> PropPair;
    QLinkedList<PropPair> properties;

    Shiboken::AutoDecRef slotAttrName(PyString_FromString(PYSIDE_SLOT_LIST_ATTR));

    while (PyDict_Next(attrs, &pos, &key, &value)) {
        if (Property::checkType(value)) {
            // Leave the properties to be register after signals because they may depend on notify signals
            int index = d.superdata->indexOfProperty(PyString_AS_STRING(key));
            if (index == -1)
                properties << PropPair(PyString_AS_STRING(key), value);
        } else if (Signal::checkType(value)) { // Register signals
            PySideSignal* data = reinterpret_cast<PySideSignal*>(value);
            const char* signalName = PyString_AS_STRING(key);
            data->signalName = strdup(signalName);
            QByteArray sig;
            sig.reserve(128);
            for (int i = 0; i < data->signaturesSize; ++i) {
                sig = signalName;
                sig += '(';
                if (data->signatures[i])
                    sig += data->signatures[i];
                sig += ')';
                if (d.superdata->indexOfSignal(sig) == -1)
                    addSignal(sig);
            }
        } else if (PyFunction_Check(value)) { // Register slots
            if (PyObject_HasAttr(value, slotAttrName)) {
                PyObject* signatureList = PyObject_GetAttr(value, slotAttrName);
                for(Py_ssize_t i = 0, i_max = PyList_Size(signatureList); i < i_max; ++i) {
                    PyObject* signature = PyList_GET_ITEM(signatureList, i);
                    QByteArray sig(PyString_AS_STRING(signature));
                    //slot the slot type and signature
                    QList<QByteArray> slotInfo = sig.split(' ');
                    int index = d.superdata->indexOfSlot(slotInfo[1]);
                    if (index == -1)
                        addSlot(slotInfo[1], slotInfo[0]);
                }
            }
        }
    }

    // Register properties
    foreach (PropPair propPair, properties)
        addProperty(propPair.first, propPair.second);

}

int DynamicQMetaObject::DynamicQMetaObjectPrivate::createMetaData(QMetaObject* metaObj, QLinkedList<QByteArray> &strings)
{
    uint n_methods = m_methods.size();
    uint n_properties = m_properties.size();
    uint n_info = m_info.size();
    int header[] = {3,                  // revision
                    0,                  // class name index in m_metadata
                    n_info, 0,          // classinfo and classinfo index
                    n_methods, 0,       // method count and method list index
                    n_properties, 0,    // prop count and prop indexes
                    0, 0,               // enum count and enum index
                    0, 0,               // constructors
                    0};                 // flags

    const int HEADER_LENGHT = sizeof(header)/sizeof(int);

    m_dataSize = HEADER_LENGHT + n_methods*5 + n_properties*4 + n_info*2 + 1;
    uint* data = reinterpret_cast<uint*>(realloc(const_cast<uint*>(metaObj->d.data), m_dataSize * sizeof(uint)));
    Q_ASSERT(data);
    std::memcpy(data, header, sizeof(header));

    registerString(m_className, strings); // register class string
    m_nullIndex = registerString("", strings); // register a null string

    metaObj->d.data = data;

    return HEADER_LENGHT;
}


void DynamicQMetaObject::DynamicQMetaObjectPrivate::updateMetaObject(QMetaObject* metaObj)
{
    uint *data = const_cast<uint*>(metaObj->d.data);
    int index = m_dataSize - 1; // remove the last 0
    QLinkedList<QByteArray> strings;

    if (!data || m_invalid) {
        if (m_invalid) {
            strings.clear();
            m_dataSize = m_stringDataSize = 0;
            m_lastMethod = m_lastInfo = m_lastProperty = 0;
            m_invalid = false;
        }

        index = createMetaData(metaObj, strings);
        data = const_cast<uint*>(metaObj->d.data);
    } else {
        int n_methods = m_methods.size() - m_lastMethod;
        int n_info = m_info.size() - m_lastInfo;
        uint n_properties = m_properties.size() - m_lastProperty;

        int extraSize = n_methods*5 + n_properties*4 + n_info*2;
        if (extraSize > 0) {
            m_dataSize += extraSize;
            //realloc data
            data = reinterpret_cast<uint*>(realloc(const_cast<uint*>(metaObj->d.data), m_dataSize * sizeof(uint)));
            Q_ASSERT(data);


            data[2] = m_info.size(); //update info size
            data[4] = m_methods.size(); //update number of methods
            data[6] = m_properties.size(); // update property size
            metaObj->d.data = data;
        } else {
            data = const_cast<uint*>(metaObj->d.data);
        }
    }

    //write class info
    if (m_info.size()) {
        if (data[3] == 0)
            data[3] = index;

        QMap<QByteArray, QByteArray>::const_iterator i = m_info.constBegin() + m_lastInfo; //TODO: info is a hash this can fail
        while (i != m_info.constEnd()) {
            int valueIndex = registerString(i.value(), strings);
            int keyIndex = registerString(i.key(), strings);
            data[index++] = keyIndex + m_stringDataSize;
            data[index++] = valueIndex + m_stringDataSize;
            i++;
        }

        m_lastInfo = m_info.size();
    }

    //write properties
    if (m_properties.size()) {
        if (data[7] == 0)
            data[7] = index;

        QList<PropertyData>::const_iterator i = m_properties.constBegin() + m_lastProperty;
        while(i != m_properties.constEnd()) {
            if (i->isValid()) {
                data[index++] = registerString(i->name(), strings) + m_stringDataSize; // name
            } else
                data[index++] = m_nullIndex;

            data[index++] = (i->isValid() ? (registerString(i->type(), strings) + m_stringDataSize) :  m_nullIndex); // normalized type
            data[index++] = i->flags();
            i++;
        }

        //write properties notify
        i = m_properties.constBegin() + m_lastProperty;
        while(i != m_properties.constEnd()) {
            data[index++] = i->notifyId() >= 0 ? i->notifyId() : 0; //signal notify index
            i++;
        }

        m_lastProperty = m_properties.size();
    }

    //write signals/slots
    if (m_methods.size()) {
        if (data[5] == 0)
            data[5] = index;

        writeMethodsData(m_methods, &data, strings, &index, m_nullIndex, AccessPublic);
    }

    data[index++] = 0; // the end

    // create the m_metadata string
    QByteArray str;
    QByteArray debugStr;
    foreach(QByteArray field, strings) {

        debugStr.append(field);
        debugStr.append('|');

        str.append(field);
        str.append(char(0));
    }

    int newSize = (m_stringDataSize + str.count()) * sizeof(char);
    char *stringdata = reinterpret_cast<char*>(realloc(const_cast<char*>(metaObj->d.stringdata), newSize));
    Q_ASSERT(stringdata);

    metaObj->d.stringdata = stringdata;

    stringdata += m_stringDataSize; //shift to the end of old position
    std::copy(str.begin(), str.end(), stringdata);

    m_stringDataSize = newSize;
    metaObj->d.data = data;
}

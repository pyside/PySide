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

#include "typeresolver.h"
#include <QHash>
#include <cstdlib>
#include <QDebug>

using namespace PySide;

static QHash<QLatin1String, TypeResolver*> typeResolverMap;

struct TypeResolver::TypeResolverPrivate
{
    const char* typeName; // maybe this is not needed anymore
    CppToPythonFunc cppToPython;
    PythonToCppFunc pythonToCpp;
    DeleteObjectFunc deleteObject;
};

static void deinitTypeResolver()
{
    qDeleteAll(typeResolverMap);
    typeResolverMap.clear();
}

static void registerTypeResolver(TypeResolver* resolver)
{
    static bool initied = false;
    if (!initied) {
        Q_ASSERT(typeResolverMap.isEmpty());
        initied = true;
        std::atexit(deinitTypeResolver);
        TypeResolver::createValueTypeResolver<double>("double");
        TypeResolver::createValueTypeResolver<float>("float");
        TypeResolver::createValueTypeResolver<qreal>("qreal");
        TypeResolver::createValueTypeResolver<bool>("bool");
        TypeResolver::createValueTypeResolver<int>("int");
        TypeResolver::createValueTypeResolver<qint64>("qint64");
    }
    Q_ASSERT(!typeResolverMap.contains(QLatin1String(resolver->typeName())));
    typeResolverMap[QLatin1String(resolver->typeName())] = resolver;
}

TypeResolver::TypeResolver(const char* typeName, TypeResolver::CppToPythonFunc cppToPy, TypeResolver::PythonToCppFunc pyToCpp, TypeResolver::DeleteObjectFunc deleter)
{
    m_d = new TypeResolverPrivate;
    m_d->typeName = typeName;
    m_d->cppToPython = cppToPy;
    m_d->pythonToCpp = pyToCpp;
    m_d->deleteObject = deleter;

    registerTypeResolver(this);
}

TypeResolver::~TypeResolver()
{
    delete m_d;
}

PySide::TypeResolver* TypeResolver::get(const QString& typeName)
{
    QByteArray data = typeName.toAscii();
    return get(data.constData());
}

PySide::TypeResolver* TypeResolver::get(const char* typeName)
{
    Q_ASSERT(typeResolverMap.contains(QLatin1String(typeName)));
    return typeResolverMap.value(QLatin1String(typeName));
}

const char* TypeResolver::typeName() const
{
    return m_d->typeName;
}

void* TypeResolver::toCpp(PyObject* pyObj)
{
    return m_d->pythonToCpp(pyObj);
}

PyObject* TypeResolver::toPython(void* cppObj)
{
    return m_d->cppToPython(cppObj);
}

void TypeResolver::deleteObject(void* object)
{
    if (m_d->deleteObject)
        m_d->deleteObject(object);
}


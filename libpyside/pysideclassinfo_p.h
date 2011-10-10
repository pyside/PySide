/*
 * This file is part of the PySide project.
 *
 * Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef PYSIDE_CLASSINFO_P_H
#define PYSIDE_CLASSINFO_P_H

#include <sbkpython.h>
#include <QMetaObject>
#include "pysideclassinfo.h"

#define __INFO_ATTR_NAME__      "__classInfo__"

struct PySideClassInfo;

extern "C"
{

struct PySideClassInfoPrivate {
    QMap<QByteArray, QByteArray> m_data;
};

} // extern "C"

namespace PySide { namespace ClassInfo {

/**
 * Init PySide QProperty support system
 */
void init(PyObject* module);


} // namespace ClassInfo
} // namespace PySide

#endif

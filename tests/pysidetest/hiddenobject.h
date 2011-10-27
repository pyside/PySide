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

#ifndef HIDDENOBJECT_H
#define HIDDENOBJECT_H

#ifdef pysidetest_EXPORTS
#define PYSIDE_EXPORTS 1
#endif
#include "pysidemacros.h"
#include <QObject>

// This class shouldn't be exported!
class HiddenObject : public QObject
{
    Q_OBJECT
public:
    HiddenObject() : m_called(false) {}
    Q_INVOKABLE void callMe();
public slots:
    bool wasCalled();
private:
    bool m_called;
};

// Return a instance of HiddenObject
PYSIDE_API QObject* getHiddenObject();


#endif

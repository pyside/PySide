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

#include "testobject.h"

void TestObject::emitIdValueSignal()
{
    emit idValue(m_idValue);
}

void TestObject::emitStaticMethodDoubleSignal()
{
    emit staticMethodDouble();
}

void TestObject::emitSignalWithDefaultValue_void()
{
    emit signalWithDefaultValue();
}

void TestObject::emitSignalWithDefaultValue_bool()
{
    emit signalWithDefaultValue(true);
}

void TestObject::emitSignalWithTypedefValue(int value)
{
    emit signalWithTypedefValue(TypedefValue(value));
}

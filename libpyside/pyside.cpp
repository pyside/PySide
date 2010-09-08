/*
 * This file is part of the Shiboken Python Bindings Generator project.
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


#include "pyside.h"
#include "signalmanager.h"
#include "qproperty.h"

extern "C" void init_signal(PyObject* module);
extern "C" void init_slot(PyObject* module);
extern "C" void init_qproperty(PyObject* module);

namespace PySide
{

void init(PyObject *module)
{
    init_signal(module);
    init_slot(module);
    init_qproperty(module);
    // Init signal manager, so it will register some meta types used by QVariant.
    SignalManager::instance();
}

} //namespace PySide


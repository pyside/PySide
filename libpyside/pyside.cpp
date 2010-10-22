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


#include "pyside.h"
#include <basewrapper.h>
#include <conversions.h>
#include <typeresolver.h>
#include <algorithm>
#include <cctype>
#include <QStack>
#include <QCoreApplication>
#include "signalmanager.h"
#include "qproperty_p.h"
#include "qproperty.h"
#include "qsignal.h"
#include "qsignal_p.h"
#include "qslot_p.h"

static QStack<PySide::CleanupFunction> cleanupFunctionList;

namespace PySide
{

void init(PyObject *module)
{
    initSignalSupport(module);
    initSlotSupport(module);
    initQProperty(module);
    // Init signal manager, so it will register some meta types used by QVariant.
    SignalManager::instance();
}

bool fillQtProperties(PyObject* qObj, const QMetaObject* metaObj, PyObject* kwds, const char** blackList, unsigned int blackListSize)
{

    PyObject *key, *value;
    Py_ssize_t pos = 0;

    while (PyDict_Next(kwds, &pos, &key, &value)) {
        if (!blackListSize || !std::binary_search(blackList, blackList + blackListSize, std::string(PyString_AS_STRING(key)))) {
            QByteArray propName(PyString_AS_STRING(key));
            if (metaObj->indexOfProperty(propName) != -1) {
                propName[0] = std::toupper(propName[0]);
                propName.prepend("set");

                Shiboken::AutoDecRef propSetter(PyObject_GetAttrString(qObj, propName.constData()));
                if (!propSetter.isNull()) {
                    Shiboken::AutoDecRef args(PyTuple_Pack(1, value));
                    Shiboken::AutoDecRef retval(PyObject_CallObject(propSetter, args));
                } else {
                    PyObject* attr = PyObject_GenericGetAttr(qObj, key);
                    if (isQPropertyType(attr))
                        PySide::qpropertySet(reinterpret_cast<PySideQProperty*>(attr), qObj, value);
                }
            } else {
                propName.append("()");
                if (metaObj->indexOfSignal(propName) != -1) {
                    propName.prepend('2');
                    PySide::signalConnect(qObj, propName, value);
                } else {
                    PyErr_Format(PyExc_AttributeError, "'%s' is not a Qt property or a signal", propName.constData());
                    return false;
                };
            }
        }
    }
    return true;
}

void registerCleanupFunction(CleanupFunction func)
{
    cleanupFunctionList.push(func);
}

void runCleanupFunctions()
{
    while (!cleanupFunctionList.isEmpty()) {
        CleanupFunction f = cleanupFunctionList.pop();
        f();
    }
}

void destroyQCoreApplication()
{
    SignalManager::instance().clear();
    QCoreApplication* app = QCoreApplication::instance();
    if (!app)
        return;

    Shiboken::BindingManager& bm = Shiboken::BindingManager::instance();
    PyObject* pyQApp = bm.retrieveWrapper(app);
    PyTypeObject* pyQObjectType = Shiboken::TypeResolver::get("QObject*")->pythonType();
    assert(pyQObjectType);

    foreach (PyObject* pyObj, bm.getAllPyObjects()) {
        if (pyObj != pyQApp && PyObject_TypeCheck(pyObj, pyQObjectType)) {
            if (SbkBaseWrapper_hasOwnership(pyObj)) {
                bm.destroyWrapper(pyObj);
                delete static_cast<QObject*>(Shiboken::getCppPointer(pyObj, Shiboken::SbkType<QObject*>()));
            }
        }
    }
    app->flush();
    delete app;
}

} //namespace PySide


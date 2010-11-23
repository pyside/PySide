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
#include "signalmanager.h"
#include "pysideproperty_p.h"
#include "pysideproperty.h"
#include "pysidesignal.h"
#include "pysidesignal_p.h"
#include "pysideslot_p.h"
#include "pysidemetafunction_p.h"

#include <basewrapper.h>
#include <conversions.h>
#include <typeresolver.h>
#include <algorithm>
#include <cctype>
#include <QStack>
#include <QCoreApplication>

static QStack<PySide::CleanupFunction> cleanupFunctionList;

namespace PySide
{

void init(PyObject *module)
{
    Signal::init(module);
    Slot::init(module);
    Property::init(module);
    MetaFunction::init(module);
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
                    if (PySide::Property::isPropertyType(attr))
                        PySide::Property::setValue(reinterpret_cast<PySideProperty*>(attr), qObj, value);
                }
            } else {
                propName.append("()");
                if (metaObj->indexOfSignal(propName) != -1) {
                    propName.prepend('2');
                    PySide::Signal::connect(qObj, propName, value);
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
    SbkObject* pyQApp = bm.retrieveWrapper(app);
    PyTypeObject* pyQObjectType = Shiboken::TypeResolver::get("QObject*")->pythonType();
    assert(pyQObjectType);

    QList<SbkObject*> objects;

    //filter only QObjects which we have ownership, this will avoid list changes during the destruction of some parent object
    foreach (SbkObject* pyObj, bm.getAllPyObjects()) {
        if (pyObj != pyQApp && PyObject_TypeCheck(pyObj, pyQObjectType)) {
            if (Shiboken::Object::hasOwnership(pyObj))
                objects << pyObj;
        }
    }

    //Now we can destroy all object in the list
    foreach (SbkObject* pyObj, objects)
        Shiboken::callCppDestructor<QObject>(Shiboken::Object::cppPointer(pyObj, Shiboken::SbkType<QObject*>()));

    // in the end destroy app
    delete app;
}

} //namespace PySide


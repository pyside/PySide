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


#include "customwidget.h"

#include <shiboken.h>

struct PyCustomWidgetPrivate
{
    PyObject* pyObject;
    bool initialized;
};

PyCustomWidget::PyCustomWidget(PyObject* objectType)
    : m_data(new PyCustomWidgetPrivate())
{
    m_data->pyObject = objectType;
}

PyCustomWidget::~PyCustomWidget()
{
}

bool PyCustomWidget::isContainer() const
{
    return false;
}

bool PyCustomWidget::isInitialized() const
{
    return m_data->initialized;
}

QIcon PyCustomWidget::icon() const
{
    return QIcon();
}

QString PyCustomWidget::domXml() const
{
    return QString();
}

QString PyCustomWidget::group() const
{
    return QString();
}

QString PyCustomWidget::includeFile() const
{
    return QString();
}

QString PyCustomWidget::name() const
{
    static QString objectName;
    if (objectName.isEmpty()) {
        objectName = QString(reinterpret_cast<PyTypeObject*>(m_data->pyObject)->tp_name);
    }
    return objectName;
}

QString PyCustomWidget::toolTip() const
{
    return QString();
}

QString PyCustomWidget::whatsThis() const
{
    return QString();
}

QWidget *PyCustomWidget::createWidget(QWidget *parent)
{
    //Create a python instance and return cpp object
    PyObject* pyParent;
    bool unkowParent = false;
    if (parent) {
        pyParent = Shiboken::BindingManager::instance().retrieveWrapper(parent);
        if (!pyParent) {
            pyParent = Shiboken::Converter<QWidget*>::toPython(parent);
            unkowParent = true;
        } else {
            Py_INCREF(pyParent);
        }
    } else {
        Py_INCREF(Py_None);
        pyParent = Py_None;
    }

    Shiboken::AutoDecRef pyArgs(PyTuple_New(1));
    PyTuple_SET_ITEM(pyArgs, 0, pyParent); //tuple will keep pyParent reference

    //Call python constructor
    PyObject* result = PyObject_CallObject(m_data->pyObject, pyArgs);

    QWidget* widget = 0;
    if (result) {
        if (unkowParent) //if parent does not exists in python, transfer the ownership to cpp
            Shiboken::BindingManager::instance().transferOwnershipToCpp(result);
        else
            Shiboken::setParent(pyParent, result);

        widget = reinterpret_cast<QWidget*>(Shiboken::getCppPointer(result, result->ob_type));
    }

    return widget;
}

void PyCustomWidget::initialize(QDesignerFormEditorInterface *core)
{
    m_data->initialized = true;
}


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
    m_name = QString(reinterpret_cast<PyTypeObject*>(objectType)->tp_name);
}

PyCustomWidget::~PyCustomWidget()
{
    delete m_data;
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
    return m_name;
}

QString PyCustomWidget::toolTip() const
{
    return QString();
}

QString PyCustomWidget::whatsThis() const
{
    return QString();
}

QWidget* PyCustomWidget::createWidget(QWidget* parent)
{
    //Create a python instance and return cpp object
    PyObject* pyParent;
    bool unkowParent = false;
    if (parent) {
        pyParent = reinterpret_cast<PyObject*>(Shiboken::BindingManager::instance().retrieveWrapper(parent));
        if (pyParent) {
            Py_INCREF(pyParent);
        } else {
            static Shiboken::Conversions::SpecificConverter converter("QWidget*");
            pyParent = converter.toPython(&parent);
            unkowParent = true;
        }
    } else {
        Py_INCREF(Py_None);
        pyParent = Py_None;
    }

    Shiboken::AutoDecRef pyArgs(PyTuple_New(1));
    PyTuple_SET_ITEM(pyArgs, 0, pyParent); //tuple will keep pyParent reference

    //Call python constructor
    SbkObject* result = reinterpret_cast<SbkObject*>(PyObject_CallObject(m_data->pyObject, pyArgs));

    QWidget* widget = 0;
    if (result) {
        if (unkowParent) //if parent does not exists in python, transfer the ownership to cpp
            Shiboken::Object::releaseOwnership(result);
        else
            Shiboken::Object::setParent(pyParent, reinterpret_cast<PyObject*>(result));

        widget = reinterpret_cast<QWidget*>(Shiboken::Object::cppPointer(result, Py_TYPE(result)));
    }

    return widget;
}

void PyCustomWidget::initialize(QDesignerFormEditorInterface* core)
{
    m_data->initialized = true;
}

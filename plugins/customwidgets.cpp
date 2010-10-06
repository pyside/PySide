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

#include "customwidgets.h"
#include "customwidget.h"

#include <shiboken.h>

struct PyCustomWidgetPrivate
{
    PyObject* pyObject;
    bool initialized;
};

struct PyCustomWidgetsPrivate
{
    QList<QDesignerCustomWidgetInterface*> widgets;
    ~PyCustomWidgetsPrivate();
};


PyCustomWidgetsPrivate::~PyCustomWidgetsPrivate()
{
    foreach(QDesignerCustomWidgetInterface* iface, widgets)
        delete iface;
    widgets.clear();
}

PyCustomWidgets::PyCustomWidgets(QObject *parent)
    : QObject(parent), m_data(new PyCustomWidgetsPrivate)
{
}

PyCustomWidgets::~PyCustomWidgets()
{
}

void PyCustomWidgets::registerWidgetType(PyObject* widget)
{
    m_data->widgets.append(new PyCustomWidget(widget));
}

QList<QDesignerCustomWidgetInterface*> PyCustomWidgets::customWidgets() const
{
    return m_data->widgets;
}

Q_EXPORT_STATIC_PLUGIN2(uiplugin, PyCustomWidgets)

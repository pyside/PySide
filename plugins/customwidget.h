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

#ifndef _PY_CUSTOM_WIDGET_H_
#define _PY_CUSTOM_WIDGET_H_

#include <QtDesigner/QtDesigner>
#include <QDesignerCustomWidgetInterface>
#include <shiboken.h>

struct PyCustomWidgetPrivate;

class PyCustomWidget: public QObject, public QDesignerCustomWidgetInterface
{
     Q_OBJECT
     Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    PyCustomWidget(PyObject* objectType);
    ~PyCustomWidget();

    bool isContainer() const;
    bool isInitialized() const;
    QIcon icon() const;
    QString domXml() const;
    QString group() const;
    QString includeFile() const;
    QString name() const;
    QString toolTip() const;
    QString whatsThis() const;
    QWidget *createWidget(QWidget *parent);
    void initialize(QDesignerFormEditorInterface *core);

private:
    QScopedPointer<PyCustomWidgetPrivate> m_data;
    
};

#endif

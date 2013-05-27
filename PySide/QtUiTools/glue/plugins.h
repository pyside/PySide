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

#ifndef _PLUGIN_H_
#define _PLUGIN_H_

#include <QPluginLoader>
#include "customwidgets.h"

inline void registerCustomWidget(PyObject* obj)
{
    static PyCustomWidgets* plugin = 0;

    if (plugin == 0) {
        foreach(QObject* o, QPluginLoader::staticInstances()) {
            plugin = qobject_cast<PyCustomWidgets*>(o);
            if (plugin)
                break;
        }
    }

    if (!plugin)
        qDebug() << "Failed to load uiloader plugin.";
    else
        plugin->registerWidgetType(obj);
}

#endif

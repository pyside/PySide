/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtTest module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef PYSIDEQTESTTOUCH_H
#define PYSIDEQTESTTOUCH_H

#include <QtTest/qtest_global.h>
#include <QtTest/qtestassert.h>
#include <QtTest/qtestsystem.h>
#include <QtTest/qtestspontaneevent.h>
#include <QtTest/qtesttouch.h>

#include <QtCore/qmap.h>
#include <QtGui/qevent.h>
#include <QtGui/qwidget.h>

QT_BEGIN_NAMESPACE

namespace QTest
{

    class PySideQTouchEventSequence
    {
    public:
        ~PySideQTouchEventSequence()
        {
            commit();
        }

        PySideQTouchEventSequence* press(int touchId, const QPoint &pt, QWidget *widget = 0)
        {
            QTouchEvent::TouchPoint &p = point(touchId);
            p.setScreenPos(mapToScreen(widget, pt));
            p.setState(Qt::TouchPointPressed);
            return this;
        }

        PySideQTouchEventSequence* move(int touchId, const QPoint &pt, QWidget *widget = 0)
        {
            QTouchEvent::TouchPoint &p = point(touchId);
            p.setScreenPos(mapToScreen(widget, pt));
            p.setState(Qt::TouchPointMoved);
            return this;
        }

        PySideQTouchEventSequence* release(int touchId, const QPoint &pt, QWidget *widget = 0)
        {
            QTouchEvent::TouchPoint &p = point(touchId);
            p.setScreenPos(mapToScreen(widget, pt));
            p.setState(Qt::TouchPointReleased);
            return this;
        }

        PySideQTouchEventSequence* stationary(int touchId)
        {
            QTouchEvent::TouchPoint &p = point(touchId);
            p.setState(Qt::TouchPointStationary);
            return this;
        }

        void commit()
        {
            qt_translateRawTouchEvent(targetWidget, deviceType, points.values());
            targetWidget = 0;
            points.clear();
        }

    private:
        PySideQTouchEventSequence(QWidget *widget, QTouchEvent::DeviceType aDeviceType)
            : targetWidget(widget), deviceType(aDeviceType)
        {
        }

        PySideQTouchEventSequence(const PySideQTouchEventSequence &v);

        void operator=(const PySideQTouchEventSequence&);

        QTouchEvent::TouchPoint &point(int touchId)
        {
            if (!points.contains(touchId))
                points[touchId] = QTouchEvent::TouchPoint(touchId);
            return points[touchId];
        }

        QPoint mapToScreen(QWidget *widget, const QPoint &pt)
        {
            if (widget)
                return widget->mapToGlobal(pt);
            return targetWidget ? targetWidget->mapToGlobal(pt) : pt;
        }

        QMap<int, QTouchEvent::TouchPoint> points;
        QWidget *targetWidget;
        QTouchEvent::DeviceType deviceType;
        friend PySideQTouchEventSequence* generateTouchEvent(QWidget *, QTouchEvent::DeviceType);
    };

    inline
    PySideQTouchEventSequence* generateTouchEvent(QWidget *widget = 0,
                                                  QTouchEvent::DeviceType deviceType = QTouchEvent::TouchScreen)
    {
        return new PySideQTouchEventSequence(widget, deviceType);
    }

}

QT_END_NAMESPACE

#endif // PYSIDEQTESTTOUCH_H

############################################################################
##
## Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
## Contact: http://www.qt-project.org/legal
##
## This file is part of the documentation of the Qt Toolkit.
##
## $QT_BEGIN_LICENSE:LGPL$
## Commercial License Usage
## Licensees holding valid commercial Qt licenses may use this file in
## accordance with the commercial license agreement provided with the
## Software or, alternatively, in accordance with the terms contained in
## a written agreement between you and Digia.  For licensing terms and
## conditions see http://qt.digia.com/licensing.  For further information
## use the contact form at http://qt.digia.com/contact-us.
##
## GNU Lesser General Public License Usage
## Alternatively, this file may be used under the terms of the GNU Lesser
## General Public License version 2.1 as published by the Free Software
## Foundation and appearing in the file LICENSE.LGPL included in the
## packaging of this file.  Please review the following information to
## ensure the GNU Lesser General Public License version 2.1 requirements
## will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
##
## In addition, as a special exception, Digia gives you certain additional
## rights.  These rights are described in the Digia Qt LGPL Exception
## version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
##
## GNU General Public License Usage
## Alternatively, this file may be used under the terms of the GNU
## General Public License version 3.0 as published by the Free Software
## Foundation and appearing in the file LICENSE.GPL included in the
## packaging of this file.  Please review the following information to
## ensure the GNU General Public License version 3.0 requirements will be
## met: http://www.gnu.org/copyleft/gpl.html.
##
##
## $QT_END_LICENSE$
##
############################################################################

//! [0]
        polygon = QPolygon()
        polygon << QPoint(10, 20) << QPoint(20, 30)
//! [0]

//! [1]
        polygon = QPolygonF()
        polygon << QPointF(10.4, 20.5) << QPointF(20.2, 30.2)
//! [1]

//! [2]
        points = [ 10, 20, 30, 40 ]
        polygon = QPolygon()
        polygon.setPoints(2, points)
//! [2]

//! [3]
        polygon = QPolygon()
        polygon.setPoints(2, 10, 20, 30, 40)
//! [3]

//! [4]
        polygon = QPolygon(1)
        polygon[0] = QPoint(4, 5)
        polygon.putPoints(1, 2, 6,7, 8,9)
//! [4]

//! [5]
        polygon = QPolygon(3)
        polygon.putPoints(0, 3, 4,5, 0,0, 8,9)
        polygon.putPoints(1, 1, 6,7)
//! [5]

//! [6]
        polygon1 = QPolygon()
        polygon1.putPoints(0, 3, 1,2, 0,0, 5,6)
        # polygon1 is now the three-point polygon(1,2, 0,0, 5,6)

        polygon2 = QPolygon()
        polygon2.putPoints(0, 3, 4,4, 5,5, 6,6)
        # polygon2 is now (4,4, 5,5, 6,6)

        polygon1.putPoints(2, 3, polygon2)
        # polygon1 is now the five-point polygon(1,2, 0,0, 4,4, 5,5, 6,6)
//! [6]


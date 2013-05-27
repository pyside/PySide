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
def paintEvent(self, event):
    painter = QPainter(self)
    painter.setPen(QPen(Qt.blue, 1, Qt.DashLine))
    painter.drawRect(0, 0, 100, 100)

    painter.rotate(45)

    painter.setFont(QFont("Helvetica", 24))
    painter.setPen(QPen(Qt.black, 1))
    painter.drawText(20, 10, "QMatrix")
//! [0]


//! [1]
def paintEvent(self, event)

    painter = QPainter(self)
    painter.setPen(QPen(Qt.blue, 1, Qt.DashLine))
    painter.drawRect(0, 0, 100, 100)

    matrix = QMatrix()
    matrix.translate(50, 50)
    matrix.rotate(45)
    matrix.scale(0.5, 1.0)
    painter.setMatrix(matrix)

    painter.setFont(QFont("Helvetica", 24))
    painter.setPen(QPen(Qt.black, 1))
    painter.drawText(20, 10, "QMatrix")

//! [1]


//! [2]
def paintEvent(self, event)

    pi = 3.14

    a    = pi/180 * 45.0
    sina = sin(a)
    cosa = cos(a)

    translationMatrix = QMatrix(1, 0, 0, 1, 50.0, 50.0)
    rotationMatrix = QMatrix(cosa, sina, -sina, cosa, 0, 0)
    scalingMatrix = QMatrix(0.5, 0, 0, 1.0, 0, 0)

    matrix = QMatrix()
    matrix =  scalingMatrix * rotationMatrix * translationMatrix

    painter = QPainter(self)
    painter.setPen(QPen(Qt.blue, 1, Qt::DashLine))
    painter.drawRect(0, 0, 100, 100)

    painter.setMatrix(matrix)

    painter.setFont(QFont("Helvetica", 24))
    painter.setPen(QPen(Qt.black, 1))
    painter.drawText(20, 10, "QMatrix")

//! [2]


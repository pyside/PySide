/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the example classes of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
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
**
** $QT_END_LICENSE$
**
****************************************************************************/

//! [0]
def __init__(self, parent):
    QAbstractItemDelegate.__init__(self, parent)
    self.pixelSize = 12
//! [0]

//! [1]
def paint(self, painter, option, index):
//! [2]
    if option.state and QStyle.State_Selected:
        painter.fillRect(option.rect, option.palette.highlight())
//! [1]

//! [3]
    size = qMin(option.rect.width(), option.rect.height())
//! [3] //! [4]
    brightness = index.model().data(index, Qt.DisplayRole).toInt()
    radius = (size/2.0) - (brightness/255.0 * size/2.0)
    if radius == 0.0:
        return
//! [4]

//! [5]
    painter.save()
//! [5] //! [6]
    painter.setRenderHint(QPainter.Antialiasing, true)
//! [6] //! [7]
    painter.setPen(Qt.NoPen)
//! [7] //! [8]
    if option.state and QStyle.State_Selected:
//! [8] //! [9]
        painter.setBrush(option.palette.highlightedText())
    else
//! [2]
        painter.setBrush(QBrush(Qt.black))
//! [9]

//! [10]
    painter.drawEllipse(QRectF(option.rect.x() + option.rect.width()/2 - radius,
                                option.rect.y() + option.rect.height()/2 - radius,
                                2*radius, 2*radius))
    painter.restore()
//! [10]

//! [11]
def sizeHint(self, option, index):
    return QSize(self.pixelSize, self.pixelSize)
//! [11]

//! [12]
def setPixelSize(self, size):
    self.pixelSize = size
//! [12]

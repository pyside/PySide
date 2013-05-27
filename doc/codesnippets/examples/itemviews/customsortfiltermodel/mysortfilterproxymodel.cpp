############################################################################
##
## Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
## Contact: http://www.qt-project.org/legal
##
## This file is part of the example classes of the Qt Toolkit.
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
def __init__(self, parent):
    QSortFilterProxyModel.__init__(self, parent)
//! [0]

//! [1]
def setFilterMinimumDate(self, date):
    self.minDate = date
    self.invalidateFilter()

//! [1]

//! [2]
def setFilterMaximumDate(self, date):
    self.maxDate = date
    self.invalidateFilter()

//! [2]

//! [3]
def filterAcceptsRow(self, sourceRow, sourceParent):
    index0 = sourceModel().index(sourceRow, 0, sourceParent)
    index1 = sourceModel().index(sourceRow, 1, sourceParent)
    index2 = sourceModel().index(sourceRow, 2, sourceParent)

    regex = filterRegExp()
    return (regex.indexIn(sourceModel().data(index0)) != -1
            or regex.indexIn(sourceModel().data(index1)) != -1
           and dateInRange(sourceModel().data(index2))
//! [3]

//! [4] //! [5]
def lessThan(self, left, right):
    leftData = sourceModel().data(left)
    rightData = sourceModel().data(right)
//! [4]

//! [6]
    if isinstance(leftData, QDateTime):
        return leftData < rightData
    else:
        emailPattern = QRegExp("([\\w\\.]*@[\\w\\.]*)")

        if left.column() == 1 && emailPattern.indexIn(leftData) != -1:
            leftData = emailPattern.cap(1)

        if right.column() == 1 && emailPattern.indexIn(rightData) != -1:
            rightData = emailPattern.cap(1)

        return leftString < rightString

//! [5] //! [6]

//! [7]
def dateInRange(self, date):
    return (!minDate.isValid() || date > minDate)
           && (!maxDate.isValid() || date < maxDate)

//! [7]

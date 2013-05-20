/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the documentation of the Qt Toolkit.
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

/*
  model.cpp

  A simple model that uses a QStringList as its data source.
*/

/*!
    Returns the number of items in the string list as the number of rows
    in the model.
*/

//! [0]
def rowCount(self, parent):
    return len(self.stringList)
//! [0]

/*!
    Returns an appropriate value for the requested data.
    If the view requests an invalid index, an invalid variant is returned.
    Any valid index that corresponds to a string in the list causes that
    string to be returned.
*/

//! [1]
def data(self, index, role):
    if not index.isValid():
        return None

    if index.row() >= stringList.size():
        return None

    if role == Qt.DisplayRole:
        return stringList[index.row()]
    else
        return None
//! [1]

/*!
    Returns the appropriate header string depending on the orientation of
    the header and the section. If anything other than the display role is
    requested, we return an invalid variant.
*/

//! [2]
def headerData(self, section, orientation, role):
    if role != Qt::DisplayRole:
        return None

    if orientation == Qt::Horizontal:
        return "Column %s" % section
    else:
        return "Row %s" % section
//! [2]

/*!
    Returns an appropriate value for the item's flags. Valid items are
    enabled, selectable, and editable.
*/

//! [3]
def flags(self, index):
    if not index.isValid()
        return Qt.ItemIsEnabled

    return QAbstractItemModel.flags(index) | Qt.ItemIsEditable
//! [3]

/*!
    Changes an item in the string list, but only if the following conditions
    are met:

    * The index supplied is valid.
    * The index corresponds to an item to be shown in a view.
    * The role associated with editing text is specified.

    The dataChanged() signal is emitted if the item is changed.
*/

//! [4]
def setData(self, index, value, role):
    if index.isValid() and role == Qt.EditRole:
        self.stringList[index.row()] = value
        self.dataChanged.emit(index, index)
        return True;
//! [4] //! [5]
    return False;
}
//! [5]

/*!
    Inserts a number of rows into the model at the specified position.
*/

//! [6]
def insertRows(self, position, rows, parent):
    self.beginInsertRows(QModelIndex(), position, position+rows-1)

    for row in range(0, rows):
        self.stringList.insert(position, "")

    self.endInsertRows()
    return True;
//! [6] //! [7]
//! [7]

/*!
    Removes a number of rows from the model at the specified position.
*/

//! [8]
def removeRows(self, position, rows, parent):
    self.beginRemoveRows(QModelIndex(), position, position+rows-1)

    for row in range(0, rows):
        del self.stringList[position]

    self.endRemoveRows()
    return True;
//! [8] //! [9]
//! [9]

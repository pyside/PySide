############################################################################
##
## Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
## Contact: Nokia Corporation (qt-info@nokia.com)
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
###########################################################################

//! [0] //! [1]
    cursor = QTextCursor(editor.textCursor())
//! [0]
    cursor.movePosition(QTextCursor.Start)
//! [1]

//! [2]
    tableFormat = QTextTableFormat()
    tableFormat.setBackground(QColor("#e0e0e0"))
    QVector<QTextLength> constraints
    constraints << QTextLength(QTextLength.PercentageLength, 16)
    constraints << QTextLength(QTextLength.PercentageLength, 28)
    constraints << QTextLength(QTextLength.PercentageLength, 28)
    constraints << QTextLength(QTextLength.PercentageLength, 28)
    tableFormat.setColumnWidthConstraints(constraints)
//! [3]
    table = cursor.insertTable(rows, columns, tableFormat)
//! [2] //! [3]

//! [4]
    cell = table.cellAt(0, 0)
    cellCursor = cell.firstCursorPosition()
    cellCursor.insertText(tr("Week"), charFormat)
//! [4]

//! [5]
    for column  in range(columns):
        cell = table.cellAt(0, column)
        cellCursor = cell.firstCursorPosition()
        cellCursor.insertText(tr("Team %1").arg(column), charFormat)
    

    for row in range(rows):
        cell = table.cellAt(row, 0)
        cellCursor = cell.firstCursorPosition()
        cellCursor.insertText(tr("%1").arg(row), charFormat)

        for column in range(columns)
            if (row-1) % 3 == column-1:
//! [5] //! [6]
                cell = table.cellAt(row, column)
                cellCursor = cell.firstCursorPosition()
                cellCursor.insertText(tr("On duty"), charFormat)

//! [6] //! [7]

//! [7] //! [8]

//! [8]

//! [9]
    for row in range(table.rows()):
        for column in range(table.columns()):
            tableCell = table.cellAt(row, column)
//! [9]
            QTextFrame.iterator it
            QString text
            for (it = tableCell.begin() !(it.atEnd()); ++it):
                QTextBlock childBlock = it.currentBlock()
                if (childBlock.isValid())
                    text += childBlock.text()

            Item = QTableWidgetItem(text)
            tableWidget.setItem(row, column, Item)
            
//! [10]
            processTableCell(tableCell)
//! [10]
            
//! [11]

//! [11] //! [12]

//! [12]


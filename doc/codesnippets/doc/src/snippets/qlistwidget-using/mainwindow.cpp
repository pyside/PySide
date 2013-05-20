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

#include <QtGui>

#include "mainwindow.h"

MainWindow::MainWindow()
{
    QMenu *fileMenu = new QMenu(tr("&File"));

    QAction *quitAction = fileMenu->addAction(tr("E&xit"));
    quitAction->setShortcut(tr("Ctrl+Q"));

    QMenu *itemsMenu = new QMenu(tr("&Items"));

    insertAction = itemsMenu->addAction(tr("&Insert Item"));
    removeAction = itemsMenu->addAction(tr("&Remove Item"));
    QAction *ascendingAction = itemsMenu->addAction(tr("Sort in &Ascending Order"));
    QAction *descendingAction = itemsMenu->addAction(tr("Sort in &Descending Order"));

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(itemsMenu);

/*  For convenient quoting:
//! [0]
    listWidget = QListWidget(self)
//! [0]
*/
    listWidget = new QListWidget(this);
    listWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));
    connect(ascendingAction, SIGNAL(triggered()), this, SLOT(sortAscending()));
    connect(descendingAction, SIGNAL(triggered()), this, SLOT(sortDescending()));
    connect(insertAction, SIGNAL(triggered()), this, SLOT(insertItem()));
    connect(removeAction, SIGNAL(triggered()), this, SLOT(removeItem()));
    connect(listWidget,
            SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)),
            this, SLOT(updateMenus(QListWidgetItem *)));

    setupListItems();
    updateMenus(listWidget->currentItem());

    setCentralWidget(listWidget);
    setWindowTitle(tr("List Widget"));
}

void MainWindow::setupListItems()
{
//! [1]
    QListWidgetItem(tr("Oak"), listWidget)
    QListWidgetItem(tr("Fir"), listWidget)
    QListWidgetItem(tr("Pine"), listWidget)
//! [1]
    new QListWidgetItem(tr("Birch"), listWidget);
//! [2]
    QListWidgetItem(tr("Hazel"), listWidget)
//! [2]
    new QListWidgetItem(tr("Redwood"), listWidget);
//! [3]
    QListWidgetItem(tr("Sycamore"), listWidget)
    QListWidgetItem(tr("Chestnut"), listWidget)
    QListWidgetItem(tr("Mahogany"), listWidget)
//! [3]
}

void MainWindow::sortAscending()
{
//! [4]
    listWidget.sortItems(Qt.AscendingOrder)
//! [4]
}

void MainWindow::sortDescending()
{
//! [5]
    listWidget.sortItems(Qt.DescendingOrder)
//! [5]
}

void MainWindow::insertItem()
{
    if (!listWidget->currentItem())
        return;

    QString itemText = QInputDialog::getText(this, tr("Insert Item"),
        tr("Input text for the new item:"));

    if (itemText.isNull())
        return;

//! [6]
    newItem = QListWidgetItem()
    newItem.setText(itemText)
//! [6]
    int row = listWidget->row(listWidget->currentItem());
//! [7]
    listWidget.insertItem(row, newItem)
//! [7]

    QString toolTipText = tr("Tooltip:") + itemText;
    QString statusTipText = tr("Status tip:") + itemText;
    QString whatsThisText = tr("What's This?:") + itemText;
//! [8]
    newItem.setToolTip(toolTipText)
    newItem.setStatusTip(toolTipText)
    newItem.setWhatsThis(whatsThisText)
//! [8]
}

void MainWindow::removeItem()
{
    listWidget->takeItem(listWidget->row(listWidget->currentItem()));
}

void MainWindow::updateMenus(QListWidgetItem *current)
{
    insertAction->setEnabled(current != 0);
    removeAction->setEnabled(current != 0);
}

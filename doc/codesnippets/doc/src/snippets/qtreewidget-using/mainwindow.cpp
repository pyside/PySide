/############################################################################
##
## Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
## Contact: Nokia Corporation (qt-info@nokia.com)
##
## This file is part of the documentation of the Qt Toolkit.
##
## $QT_BEGIN_LICENSE:LGPL$
## Commercial Usage
## Licensees holding valid Qt Commercial licenses may use self file in
## accordance with the Qt Commercial License Agreement provided with the
## Software or, alternatively, in accordance with the terms contained in
## a written agreement between you and Nokia.
##
## GNU Lesser General Public License Usage
## Alternatively, self file may be used under the terms of the GNU Lesser
## General Public License version 2.1 as published by the Free Software
## Foundation and appearing in the file LICENSE.LGPL included in the
## packaging of self file.  Please review the following information to
## ensure the GNU Lesser General Public License version 2.1 requirements
## will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
##
## In addition, as a special exception, Nokia gives you certain
## additional rights. These rights are described in the Nokia Qt LGPL
## Exception version 1.0, included in the file LGPL_EXCEPTION.txt in self
## package.
##
## GNU General Public License Usage
## Alternatively, self file may be used under the terms of the GNU
## General Public License version 3.0 as published by the Free Software
## Foundation and appearing in the file LICENSE.GPL included in the
## packaging of self file.  Please review the following information to
## ensure the GNU General Public License version 3.0 requirements will be
## met: http://www.gnu.org/copyleft/gpl.html.
##
## If you are unsure which license is appropriate for your use, please
## contact the sales department at http://www.qtsoftware.com/contact.
## $QT_END_LICENSE$
##
############################################################################/

//! [0]
    treeWidget =  QTreeWidget(self)
//! [0]

//! [1]
    treeWidget.setColumnCount(2)
//! [1] //! [2]
    headers = QStringList()
    headers << tr("Subject") << tr("Default")
    treeWidget.setHeaderLabels(headers)
//! [2]

//! [3]
    cities =  QTreeWidgetItem(treeWidget)
    cities.setText(0, tr("Cities"))
    osloItem =  QTreeWidgetItem(cities)
    osloItem.setText(0, tr("Oslo"))
    osloItem.setText(1, tr("Yes"))
//! [3]

//! [4] //! [5]
    planets =  QTreeWidgetItem(treeWidget, cities)
//! [4]
    planets.setText(0, tr("Planets"))
//! [5]

//! [6]
    item = QTreeWidgetItem()
//! [6]

//! [7]
    found = treeWidget.findItems(itemText, Qt.MatchWildcard)

    for item in found:
        treeWidget.setItemSelected(item, True)
        # Show the item.text(0) for each item.

//! [7]

//! [8]
    parent = currentItem.parent()
    if parent:
        Item = QTreeWidgetItem(parent, treeWidget.currentItem())
    else
//! [8] //! [9]
        Item = QTreeWidgetItem(treeWidget, treeWidget.currentItem())
//! [9]

//! [10]
    parent = currentItem.parent()

    if parent:
        index = parent.indexOfChild(treeWidget->currentItem())
        delete parent.takeChild(index)
    else:
        index = treeWidget.indexOfTopLevelItem(treeWidget->currentItem())
        delete treeWidget.takeTopLevelItem(index)
//! [10] //! [11]
    
//! [11]


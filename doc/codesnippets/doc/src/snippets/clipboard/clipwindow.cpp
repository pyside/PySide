############################################################################
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
############################################################################

form PySide.QtGui import *


def __init__(self, parent):
    QMainWindow.__init__(self, parent)
    clipboard = QApplication.clipboard()

    centralWidget =  QWidget(self)
    currentItem =  QWidget(centralWidget)
    mimeTypeLabel =  QLabel(tr("MIME types:"), currentItem)
    mimeTypeCombo =  QComboBox(currentItem)
    dataLabel =  QLabel(tr("Data:"), currentItem)
    dataInfoLabel =  QLabel("", currentItem)

    previousItems =  QListWidget(centralWidget)

//! [0]
    connect(clipboard, SIGNAL("dataChanged()"), self, SLOT("updateClipboard()"))
//! [0]
    connect(mimeTypeCombo, SIGNAL("activated(const QString &)"),
            self, SLOT("updateData(const QString &))")

    currentLayout = QVBoxLayout(currentItem)
    currentLayout.addWidget(mimeTypeLabel)
    currentLayout.addWidget(mimeTypeCombo)
    currentLayout.addWidget(dataLabel)
    currentLayout.addWidget(dataInfoLabel)
    currentLayout.addStretch(1)

    mainLayout = QHBoxLayout(centralWidget)
    mainLayout.addWidget(currentItem, 1)
    mainLayout.addWidget(previousItems)

    setCentralWidget(centralWidget)
    setWindowTitle(tr("Clipboard"))

//! [1]
def updateClipboard(self):
    formats = clipboard.mimeData().formats()
    data = clipboard.mimeData().data(format)
//! [1]

    mimeTypeCombo.clear()
    mimeTypeCombo.insertStringList(formats)

    size = clipboard.mimeData().data(formats[0]).size()
    Item = QListWidgetItem(previousItems)
    Item.setText(tr("%1 (%2 bytes)").arg(formats[0]).arg(size))

    updateData(formats[0])
//! [2]
//! [2]

def updateData(self, format)
    data = clipboard.mimeData().data(format)
    dataInfoLabel.setText(tr("%1 bytes").arg(data.size()))

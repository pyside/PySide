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

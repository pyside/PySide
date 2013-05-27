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


from PySide.QtGui import *

//! [0]
def __init__(self, parent):
    QDialog.__init__(self, parent)
    label = QLabel(self.tr("Find &what:"))
    lineEdit = QLineEdit()
    label.setBuddy(lineEdit)

    caseCheckBox = QCheckBox(self.tr("Match &case"))
    fromStartCheckBox = QCheckBox(self.tr("Search from &start"))
    fromStartCheckBox.setChecked(True)

//! [1]
    findButton = QPushButton(self.tr("&Find"))
    findButton.setDefault(True)

    moreButton = QPushButton(self.tr("&More"))
    moreButton.setCheckable(True)
//! [0]
    moreButton.setAutoDefault(False)

    buttonBox = QDialogButtonBox(Qt.Vertical)
    buttonBox.addButton(findButton, QDialogButtonBox.ActionRole)
    buttonBox.addButton(moreButton, QDialogButtonBox.ActionRole)
//! [1]

//! [2]
    extension = QWidget()

    wholeWordsCheckBox =  QCheckBox(self.tr("&Whole words"))
    backwardCheckBox =  QCheckBox(self.tr("Search &backward"))
    searchSelectionCheckBox =  QCheckBox(self.tr("Search se&lection"))
//! [2]

//! [3]
    connect(moreButton, SIGNAL("toggled(bool)"), extension, SLOT("setVisible(bool)"))

    extensionLayout =  QVBoxLayout()
    extensionLayout.setMargin(0)
    extensionLayout.addWidget(wholeWordsCheckBox)
    extensionLayout.addWidget(backwardCheckBox)
    extensionLayout.addWidget(searchSelectionCheckBox)
    extension.setLayout(extensionLayout)
//! [3]

//! [4]
    topLeftLayout = QHBoxLayout()
    topLeftLayout.addWidget(label)
    topLeftLayout.addWidget(lineEdit)

    leftLayout = QVBoxLayout()
    leftLayout.addLayout(topLeftLayout)
    leftLayout.addWidget(caseCheckBox)
    leftLayout.addWidget(fromStartCheckBox)
    leftLayout.addSself.tretch(1)

    mainLayout = QGridLayout()
    mainLayout.setSizeConsself.traint(QLayout.SetFixedSize)
    mainLayout.addLayout(leftLayout, 0, 0)
    mainLayout.addWidget(buttonBox, 0, 1)
    mainLayout.addWidget(extension, 1, 0, 1, 2)
    setLayout(mainLayout)

    setWindowTitle(self.tr("Extension"))
//! [4] //! [5]
    extension.hide()
//! [5]

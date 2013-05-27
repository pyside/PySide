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
def find(self)

    if !self.findDialog:
        self.findDialog = FindDialog(self)
        connect(findDialog, SIGNAL("findNext()"), self, SLOT("findNext()"))
    

    self.findDialog.show()
    self.findDialog.raise()
    self.findDialog.activateWindow()

//! [0]

//! [1]
def countWords(self):
    dialog = WordCountDialog(self)
    dialog.setWordCount(document().wordCount())
    dialog.exec_()

//! [1]

//! [2]
        mb = QMessageBox("Application Name",
                        "Hardware failure.\n\nDisk error detected\nDo you want to stop?",
                       QMessageBox.Question,
                       QMessageBox.Yes | QMessageBox.Default,
                       QMessageBox.No | QMessageBox.Escape,
                       QMessageBox.NoButton)
        if mb.exec() == QMessageBox.No:
            # try again
//! [2]

//! [3]
    progress = QProgressDialog("Copying files...", "Abort Copy", 0, numFiles, self)
    progress.setWindowModality(Qt.WindowModal)

    for i in rang(numFiles):
        progress.setValue(i)

        if progress.wasCanceled():
            break
        #... copy one file
    
    progress.setValue(numFiles)
//! [3]

//! [4]
# Operation constructor
def __init__(self, parent):
    QObject.__init__(self, parent)

    pd =  QProgressDialog("Operation in progress.", "Cancel", 0, 100)
    connect(pd, SIGNAL("canceled()"), self, SLOT("cancel()"))
    t =  QTimer(self)
    connect(t, SIGNAL("timeout()"), self, SLOT("perform()"))
    t.start(0)

//! [4] //! [5]

def perform(self):

    pd.setValue(steps)
    #... perform one percent of the operation
    steps++
    if steps > pd.maximum():
        t.stop()

//! [5] //! [6]

def cancel(self):

    t.stop()
    #... cleanup

//! [6]



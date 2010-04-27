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



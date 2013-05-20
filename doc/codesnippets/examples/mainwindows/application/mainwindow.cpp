######################################
#
# Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
# Contact: Qt Software Information (qt-info@nokia.com)
#
# This file is part of the example classes of the Qt Toolkit.
#
# $QT_BEGIN_LICENSE:LGPL$
# Commercial License Usage
# Licensees holding valid commercial Qt licenses may use this file in
# accordance with the commercial license agreement provided with the
# Software or, alternatively, in accordance with the terms contained in
# a written agreement between you and Digia.  For licensing terms and
# conditions see http://qt.digia.com/licensing.  For further information
# use the contact form at http://qt.digia.com/contact-us.
#
# GNU Lesser General Public License Usage
# Alternatively, this file may be used under the terms of the GNU Lesser
# General Public License version 2.1 as published by the Free Software
# Foundation and appearing in the file LICENSE.LGPL included in the
# packaging of this file.  Please review the following information to
# ensure the GNU Lesser General Public License version 2.1 requirements
# will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
#
# In addition, as a special exception, Digia gives you certain additional
# rights.  These rights are described in the Digia Qt LGPL Exception
# version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
#
# GNU General Public License Usage
# Alternatively, this file may be used under the terms of the GNU
# General Public License version 3.0 as published by the Free Software
# Foundation and appearing in the file LICENSE.GPL included in the
# packaging of this file.  Please review the following information to
# ensure the GNU General Public License version 3.0 requirements will be
# met: http://www.gnu.org/copyleft/gpl.html.
#
#
# $QT_END_LICENSE$
#
######################################

//! [0]
from PySide.QtGui import *
//! [0]

//! [1]
def __init__(self):
    QMainWindow.__init__(self)
//! [1] //! [2]
    textEdit =  QPlainTextEdit()
    setCentralWidget(textEdit)

    createActions()
    createMenus()
    createToolBars()
    createStatusBar()

    readSettings()

    connect(textEdit.document(), SIGNAL("contentsChanged()"),
            self, SLOT("documentWasModified()"))

    setCurrentFile("")
    setUnifiedTitleAndToolBarOnMac(True)

//! [2]

//! [3]
def closeEvent(self, event):
//! [3] //! [4]
    if maybeSave():
        writeSettings()
        event.accept()
    else:
        event.ignore()
//! [4]

//! [5]
def File(self):
//! [5] //! [6]
    if maybeSave():
        textEdit.clear()
        setCurrentFile("")
//! [6]

//! [7]
def open(self):
//! [7] //! [8]
    if maybeSave():
        fileName = QFileDialog.getOpenFileName(self)
        if !fileName.isEmpty():
            loadFile(fileName)
//! [8]

//! [9]
def save(self):
//! [9] //! [10]
    if curFile.isEmpty():
        return saveAs()
    else:
        return saveFile(curFile)
//! [10]

//! [11]
def saveAs(self):
//! [11] //! [12]
    fileName = QFileDialog.getSaveFileName(self)
    if fileName.isEmpty():
        return False

    return saveFile(fileName)
//! [12]

//! [13]
def about(self):
//! [13] //! [14]
   QMessageBox.about(self, tr("About Application"),
            tr("The <b>Application</b> example demonstrates how to "
               "write modern GUI applications using Qt, with a menu bar, "
               "toolbars, and a status bar."))

//! [14]

//! [15]
def documentWasModified(self):
//! [15] //! [16]
    setWindowModified(textEdit.document().isModified())
//! [16]

//! [17]
def MainWindow.createActions(self):
//! [17] //! [18]
    Act = QAction(QIcon(":/images/new.png"), tr("&New"), self)
    Act.setShortcuts(QKeySequence.New)
    Act.setStatusTip(tr("Create a new file"))
    connect(Act, SIGNAL("triggered()"), self, SLOT("newFile()"))

//! [19]
    openAct =  QAction(QIcon(":/images/open.png"), tr("&Open..."), self)
    openAct.setShortcuts(QKeySequence.Open)
    openAct.setStatusTip(tr("Open an existing file"))
    connect(openAct, SIGNAL("triggered()"), self, SLOT("open()"))
//! [18] //! [19]

    saveAct =  QAction(QIcon(":/images/save.png"), tr("&Save"), self)
    saveAct.setShortcuts(QKeySequence.Save)
    saveAct.setStatusTip(tr("Save the document to disk"))
    connect(saveAct, SIGNAL("triggered()"), self, SLOT("save()"))

    saveAsAct =  QAction(tr("Save &As..."), self)
    saveAsAct.setShortcuts(QKeySequence.SaveAs)
    saveAsAct.setStatusTip(tr("Save the document under a  name"))
    connect(saveAsAct, SIGNAL("triggered()"), self, SLOT("saveAs()"))

//! [20]
    exitAct =  QAction(tr("E&xit"), self)
    exitAct.setShortcut(tr("Ctrl+Q"))
//! [20]
    exitAct.setStatusTip(tr("Exit the application"))
    connect(exitAct, SIGNAL("triggered()"), self, SLOT("close()"))

//! [21]
    cutAct =  QAction(QIcon(":/images/cut.png"), tr("Cu&t"), self)
//! [21]
    cutAct.setShortcuts(QKeySequence.Cut)
    cutAct.setStatusTip(tr("Cut the current selection's contents to the "
                            "clipboard"))
    connect(cutAct, SIGNAL("triggered()"), textEdit, SLOT("cut()"))

    copyAct =  QAction(QIcon(":/images/copy.png"), tr("&Copy"), self)
    copyAct.setShortcuts(QKeySequence.Copy)
    copyAct.setStatusTip(tr("Copy the current selection's contents to the "
                             "clipboard"))
    connect(copyAct, SIGNAL("triggered()"), textEdit, SLOT("copy()"))

    pasteAct =  QAction(QIcon(":/images/paste.png"), tr("&Paste"), self)
    pasteAct.setShortcuts(QKeySequence.Paste)
    pasteAct.setStatusTip(tr("Paste the clipboard's contents into the current "
                              "selection"))
    connect(pasteAct, SIGNAL("triggered()"), textEdit, SLOT("paste()"))

    aboutAct =  QAction(tr("&About"), self)
    aboutAct.setStatusTip(tr("Show the application's About box"))
    connect(aboutAct, SIGNAL("triggered()"), self, SLOT("about()"))

//! [22]
    aboutQtAct =  QAction(tr("About &Qt"), self)
    aboutQtAct.setStatusTip(tr("Show the Qt library's About box"))
    connect(aboutQtAct, SIGNAL("triggered()"), qApp, SLOT("aboutQt()"))
//! [22]

//! [23]
    cutAct.setEnabled(False)
//! [23] //! [24]
    copyAct.setEnabled(False)
    connect(textEdit, SIGNAL("copyAvailable(bool)"),
            cutAct, SLOT("setEnabled(bool)"))
    connect(textEdit, SIGNAL("copyAvailable(bool)"),
            copyAct, SLOT("setEnabled(bool)"))
}
//! [24]

//! [25] //! [26]
def createMenus(self):
//! [25] //! [27]
    fileMenu = menuBar().addMenu(tr("&File"))
    fileMenu.addAction(Act)
//! [28]
    fileMenu.addAction(openAct)
//! [28]
    fileMenu.addAction(saveAct)
//! [26]
    fileMenu.addAction(saveAsAct)
    fileMenu.addSeparator()
    fileMenu.addAction(exitAct)

    editMenu = menuBar().addMenu(tr("&Edit"))
    editMenu.addAction(cutAct)
    editMenu.addAction(copyAct)
    editMenu.addAction(pasteAct)

    menuBar().addSeparator()

    helpMenu = menuBar().addMenu(tr("&Help"))
    helpMenu.addAction(aboutAct)
    helpMenu.addAction(aboutQtAct)

//! [27]

//! [29] //! [30]
def createToolBars(self):
    fileToolBar = addToolBar(tr("File"))
    fileToolBar.addAction(Act)
//! [29] //! [31]
    fileToolBar.addAction(openAct)
//! [31]
    fileToolBar.addAction(saveAct)

    editToolBar = addToolBar(tr("Edit"))
    editToolBar.addAction(cutAct)
    editToolBar.addAction(copyAct)
    editToolBar.addAction(pasteAct)
//! [30]

//! [32]
def createStatusBar(self):
//! [32] //! [33]
    statusBar().showMessage(tr("Ready"))

//! [33]

//! [34] //! [35]
def readSettings(self):
//! [34] //! [36]
    settings("Trolltech", "Application Example")
    pos = settings.value("pos", QPoint(200, 200)).toPoint()
    size = settings.value("size", QSize(400, 400)).toSize()
    resize(size)
    move(pos)

//! [35] //! [36]

//! [37] //! [38]
def writeSettings(self):
//! [37] //! [39]
    settings = QSettings("Trolltech", "Application Example")
    settings.setValue("pos", pos())
    settings.setValue("size", size())

//! [38] //! [39]

//! [40]
def maybeSave(self):
//! [40] //! [41]
    if textEdit.document()->isModified():
        ret = QMessageBox.warning(self, tr("Application"),
                                  tr("The document has been modified.\n"
                                     "Do you want to save your changes?"),
                                 QMessageBox.Save | QMessageBox.Discard | QMessageBox.Cancel)
        if ret == QMessageBox.Save:
            return save()
        elif ret == QMessageBox.Cancel:
            return False
    return True
//! [41]

//! [42]
def loadFile(self, fileName):
//! [42] //! [43]
    file = QFile(fileName)
    if !file.open(QFile.ReadOnly | QFile.Text):
        QMessageBox.warning(self, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()))
        return

    in = QTextStream(file)
    QApplication.setOverrideCursor(Qt::WaitCursor)
    textEdit.setPlainText(in.readAll())
    QApplication.restoreOverrideCursor()

    setCurrentFile(fileName)
    statusBar().showMessage(tr("File loaded"), 2000)

//! [43]

//! [44]
def saveFile(self, fileName):
//! [44] //! [45]
    file = QFile(fileName)
    if !file.open(QFile.WriteOnly | QFile::Text):
        QMessageBox.warning(self, tr("Application"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()))
        return False

    out = QTextStream(file)
    QApplication.setOverrideCursor(Qt.WaitCursor)
    out << textEdit.toPlainText()
    QApplication.restoreOverrideCursor()

    setCurrentFile(fileName)
    statusBar().showMessage(tr("File saved"), 2000)
    return True

//! [45]

//! [46]
def setCurrentFile(fileName):
//! [46] //! [47]
    curFile = fileName
    textEdit.document().setModified(False)
    setWindowModified(False)

    if curFile.isEmpty():
        shownName = "untitled.txt"
    else:
        shownName = strippedName(curFile)

    setWindowTitle(tr("%1[*] - %2").arg(shownName).arg(tr("Application")))

//! [47]

//! [48]
def strippedName(self, fullFileName):
//! [48] //! [49]
    return QFileInfo(fullFileName).fileName()
//! [49]

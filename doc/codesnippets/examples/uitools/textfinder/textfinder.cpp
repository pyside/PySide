/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtUiTools>
#include <QtGui>
#include "textfinder.h"

//! [0]
def __init__(self, parent = None):
    QWidget.__init__(self. parent)
    formWidget = self.loadUiFile()

//! [1]
    self.ui_findButton = qFindChild(QPushButton, self, "findButton")
    self.ui_textEdit = qFindChild(QTextEdit, self, "textEdit")
    self.ui_lineEdit = qFindChild(QLineEdit, self, "lineEdit")
//! [0] //! [1]

//! [2]
    QMetaObject.connectSlotsByName(self)
//! [2]

//! [3a]
    self.loadTextFile()
//! [3a]

//! [3b]
    layout = QVBoxLayout()
    layout.addWidget(formWidget)
    self.setLayout(layout)
//! [3b]

//! [3c]
    self.setWindowTitle("Text Finder")
    self.isFirstTime = True
//! [3c]

//! [4]
def loadUiFile(self):
    loader = QUiLoader()
    return loader.load(":/forms/textfinder.ui", self)
//! [4]

//! [5]
def loadTextFile(self):
    inputFile = QFile(":/forms/input.txt")
    inputFile.open(QIODevice.ReadOnly)
    in = QTextStream(inputFile)
    line = in.readAll()
    inputFile.close()

    self.ui_textEdit.append(line)
    self.ui_textEdit.setUndoRedoEnabled(False)
    self.ui_textEdit.setUndoRedoEnabled(True)
//! [5]

//! [6] //! [7]
@Slot()
def on_findButton_clicked(self):
    searchString = self.ui_lineEdit.text()
    document = self.ui_textEdit.document()

    found = False

    if not self.isFirstTime:
        document.undo()

    if not searchString:
        QMessageBox.information(self, "Empty Search Field",
                "The search field is empty. Please enter a word and click Find.")
    else:
        highlightCursor = QTextCursor(document)
        cursor = QTextCursor(document)
        cursor.beginEditBlock()
//! [6]
        plainFormat = QTextCharFormat(highlightCursor.charFormat())
        colorFormat = QTextCharFormat(plainFormat)
        colorFormat.setForeground(Qt.red)

        while not highlightCursor.isNull() and not highlightCursor.atEnd():
            highlightCursor = document.find(searchString, highlightCursor, QTextDocument.FindWholeWords)

            if not highlightCursor.isNull():
                found = True
                highlightCursor.movePosition(QTextCursor.WordRight, QTextCursor.KeepAnchor)
                highlightCursor.mergeCharFormat(colorFormat)
//! [8]
        cursor.endEditBlock()
//! [7] //! [9]
        self.isFirstTime = False

        if not found:
            QMessageBox.information(self, "Word Not Found", "Sorry, the word cannot be found.");
//! [8] //! [9]

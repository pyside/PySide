from PySide import QtGui, QtCore
from helper import UsesQApplication

import unittest

class MyWindow(QtGui.QMainWindow):
    appendText = QtCore.Signal(str)

    @QtCore.Slot()
    def onButtonPressed(self):
        self.appendText.emit("PySide")

    def __init__(self, parent=None):
        super(MyWindow, self).__init__(parent)

        self.textEdit = QtGui.QTextEdit()
        self.btn = QtGui.QPushButton("ClickMe")
        self.btn.clicked.connect(self.onButtonPressed)
        self.appendText.connect(self.textEdit.append)

    def start(self):
        self.btn.click()

    def text(self):
        return self.textEdit.toPlainText()


class testSignalWithCPPSlot(UsesQApplication):

    def testEmission(self):
        w = MyWindow()
        w.start()
        self.assertEqual(w.text(), "PySide")

if __name__ == '__main__':
    unittest.main()


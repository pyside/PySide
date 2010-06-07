import unittest
import sys

from PySide import QtGui
from PySide import QtCore

from helper import UsesQApplication

class MainWindow(QtGui.QMainWindow):
    def __init__(self):
        QtGui.QMainWindow.__init__(self)

        self.createToolbar()

    def createToolbar(self):
        pointerButton = QtGui.QToolButton()
        pointerToolbar = self.addToolBar("Pointer type")
        pointerToolbar.addWidget(pointerButton)


class TestMainWindow(UsesQApplication):

    def testCreateToolbar(self):
        w = MainWindow()
        w.show()
        QtCore.QTimer.singleShot(1000, self.app.quit)
        self.app.exec_()


if __name__ == '__main__':
    unittest.main()


import unittest
import sys
import weakref

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

class MyButton(QtGui.QPushButton):
    def __init__(self, parent=None):
        QtGui.QPushButton.__init__(self)
        self._called = False

    def myCallback(self):
        self._called = True


class TestMainWindow(UsesQApplication):

    def testCreateToolbar(self):
        w = MainWindow()
        w.show()
        QtCore.QTimer.singleShot(1000, self.app.quit)
        self.app.exec_()

    def objDel(self, obj):
        self.app.quit()

    def testRefCountToNull(self):
        w = QtGui.QMainWindow()
        c = QtGui.QWidget()
        self.assertEqual(sys.getrefcount(c), 2)
        w.setCentralWidget(c)
        self.assertEqual(sys.getrefcount(c), 3)
        wr = weakref.ref(c, self.objDel)
        w.setCentralWidget(None)
        c = None
        self.app.exec_()

    def testRefCountToAnother(self):
        w = QtGui.QMainWindow()
        c = QtGui.QWidget()
        self.assertEqual(sys.getrefcount(c), 2)
        w.setCentralWidget(c)
        self.assertEqual(sys.getrefcount(c), 3)

        c2 = QtGui.QWidget()
        w.setCentralWidget(c2)
        self.assertEqual(sys.getrefcount(c2), 3)

        wr = weakref.ref(c, self.objDel)
        w.setCentralWidget(None)
        c = None

        self.app.exec_()

    def testSignalDisconect(self):
        w = QtGui.QMainWindow()
        b = MyButton("button")
        b.clicked.connect(b.myCallback)
        w.setCentralWidget(b)

        b = MyButton("button")
        b.clicked.connect(b.myCallback)
        w.setCentralWidget(b)

        b.click()
        self.assertEqual(b._called, True)


if __name__ == '__main__':
    unittest.main()


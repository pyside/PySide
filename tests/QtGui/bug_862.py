
from PySide.QtCore import QObject
from PySide.QtGui import *
import PySide.QtCore
import unittest

class MyQObject(QObject):
    def __init__(self):
        QObject.__init__(self)

class MyQWidget(QWidget):
    def __init__(self):
        QWidget.__init__(self)

class MyQGraphicsObject(QGraphicsObject):
    def __init__(self):
        QGraphicsObject.__init__(self)

class MyQGraphicsItem(QGraphicsItem):
    def __init__(self):
        QGraphicsItem.__init__(self)

class TestRepr (unittest.TestCase):

    def testIt(self):

        app = QApplication([])

        self.assertEqual("<__main__.MyQObject object at ", repr(MyQObject())[:30])
        self.assertEqual("<__main__.MyQWidget object at ", repr(MyQWidget())[:30])
        self.assertEqual("<__main__.MyQGraphicsObject(this = 0x", repr(MyQGraphicsObject())[:37])
        self.assertEqual("<__main__.MyQGraphicsItem(this = 0x", repr(MyQGraphicsItem())[:35])

        self.assertEqual("<PySide.QtCore.QObject object at ", repr(QObject())[:33])
        self.assertEqual("<PySide.QtCore.QObject object at ", repr(PySide.QtCore.QObject())[:33])
        self.assertEqual("<PySide.QtGui.QWidget object at ", repr(QWidget())[:32])
        self.assertEqual("<PySide.QtGui.QGraphicsWidget(this = 0x", repr(QGraphicsWidget())[:39])

if __name__ == "__main__":
    unittest.main()

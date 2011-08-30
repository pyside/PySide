import unittest
from PySide.QtCore import QObject
from PySide.QtGui import QPen, QBrush

class TestBug991 (unittest.TestCase):
    def testReprFunction(self):
        reprPen = repr(QPen())
        self.assertTrue(reprPen.startswith("<PySide.QtGui.QPen"))
        reprBrush = repr(QBrush())
        self.assertTrue(reprBrush.startswith("<PySide.QtGui.QBrush"))
        reprObject = repr(QObject())
        self.assertTrue(reprObject.startswith("<PySide.QtCore.QObject"))

if __name__ == '__main__':
    unittest.main()

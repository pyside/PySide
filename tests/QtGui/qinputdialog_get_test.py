import unittest

from PySide import QtCore, QtGui
from helper import UsesQApplication, TimedQApplication

class TestInputDialog(TimedQApplication):

    def testGetDouble(self):
        self.assertEquals(QtGui.QInputDialog.getDouble(None, "title", "label"), (0.0, False))

    def testGetInt(self):
        self.assertEquals(QtGui.QInputDialog.getInt(None, "title", "label"), (0, False))

    def testGetInteger(self):
        self.assertEquals(QtGui.QInputDialog.getInteger(None, "title", "label"), (0, False))

    def testGetItem(self):
        (item, bool) = QtGui.QInputDialog.getItem(None, "title", "label", ["1", "2", "3"])
        self.assertEquals(str(item), "1")

    def testGetText(self):
        (text, bool) = QtGui.QInputDialog.getText(None, "title", "label")
        self.assertEquals(str(text),"")

if __name__ == '__main__':
    unittest.main()


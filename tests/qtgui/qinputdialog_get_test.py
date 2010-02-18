import unittest

from PySide import QtCore, QtGui
from helper import UsesQApplication, TimedQApplication

class TestInputDialog(TimedQApplication):

    def testGetDouble(self):
        QtGui.QInputDialog.getDouble(None, "title", "label")

    def testGetInt(self):
        QtGui.QInputDialog.getInt(None, "title", "label")

    def testGetInteger(self):
        QtGui.QInputDialog.getInteger(None, "title", "label")

    def testGetItem(self):
        QtGui.QInputDialog.getItem(None, "title", "label", QtCore.QStringList(["1", "2", "3"]))

    def testGetText(self):
        QtGui.QInputDialog.getText(None, "title", "label")

if __name__ == '__main__':
    unittest.main()


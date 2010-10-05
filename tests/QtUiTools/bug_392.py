import unittest
import os
from helper import UsesQApplication

from PySide import QtCore, QtGui, QtDeclarative
from PySide.QtUiTools import QUiLoader

class BugTest(UsesQApplication):
    def testCase(self):
        w = QtGui.QWidget()
        loader = QUiLoader()

        filePath = os.path.join(os.path.dirname(__file__), 'action.ui')
        result = loader.load(filePath, w)
        self.assertEqual(type(result.statusbar.actionFoo), QtGui.QAction)

    def testCustomWidgets(self):
        w = QtGui.QWidget()
        loader = QUiLoader()

        filePath = os.path.join(os.path.dirname(__file__), 'customwidget.ui')
        result = loader.load(filePath, w)
        self.assert_(type(result.declarativeView), QtDeclarative.QDeclarativeView)
        self.assert_(type(result.worldTimeClock), QtGui.QWidget)


if __name__ == '__main__':
    unittest.main()


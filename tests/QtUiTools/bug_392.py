import unittest
import os
from helper import UsesQApplication

from PySide import QtCore, QtGui
from PySide.QtUiTools import QUiLoader

class BugTest(UsesQApplication):
    def testCase(self):
        w = QtGui.QWidget()
        loader = QUiLoader()

        filePath = os.path.join(os.path.dirname(__file__), 'action.ui')
        result = loader.load(filePath, w)
        self.assertEqual(type(result.statusbar.actionFoo), QtGui.QAction)

if __name__ == '__main__':
    unittest.main()


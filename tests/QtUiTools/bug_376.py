import unittest
import os
from helper import UsesQApplication

from PySide import QtCore, QtGui
from PySide.QtUiTools import QUiLoader

class BugTest(UsesQApplication):
    def testCase(self):
        w = QtGui.QWidget()
        loader = QUiLoader()

        filePath = os.path.join(os.path.dirname(__file__), 'test.ui')
        result = loader.load(filePath, w)
        self.assert_(isinstance(result.child_object, QtGui.QFrame))

if __name__ == '__main__':
    unittest.main()


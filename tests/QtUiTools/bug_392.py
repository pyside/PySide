import unittest
import os
from helper import UsesQApplication

from PySide import QtGui, QtDeclarative
from PySide.QtUiTools import QUiLoader

class MyWidget(QtGui.QComboBox):
    def __init__(self, parent=None):
        QtGui.QComboBox.__init__(self, parent)

    def isPython(self):
        return True

class BugTest(UsesQApplication):
    def testCase(self):
        w = QtGui.QWidget()
        loader = QUiLoader()

        filePath = os.path.join(os.path.dirname(__file__), 'action.ui')
        result = loader.load(filePath, w)
        self.assert_(isinstance(result.statusbar.actionFoo, QtGui.QAction))

    def testCustomWidgets(self):
        w = QtGui.QWidget()
        loader = QUiLoader()

        filePath = os.path.join(os.path.dirname(__file__), 'customwidget.ui')
        result = loader.load(filePath, w)
        self.assert_(isinstance(result.declarativeView, QtDeclarative.QDeclarativeView))
        self.assert_(isinstance(result.worldTimeClock, QtGui.QWidget))

    def testPythonCustomWidgets(self):
        w = QtGui.QWidget()
        loader = QUiLoader()
        loader.registerCustomWidget(MyWidget)

        filePath = os.path.join(os.path.dirname(__file__), 'pycustomwidget.ui')
        result = loader.load(filePath, w)
        self.assert_(isinstance(result.custom, MyWidget))
        self.assert_(result.custom.isPython())

    def testPythonCustomWidgetsTwice(self):
        w = QtGui.QWidget()
        loader = QUiLoader()
        loader.registerCustomWidget(MyWidget)

        filePath = os.path.join(os.path.dirname(__file__), 'pycustomwidget2.ui')
        result = loader.load(filePath, w)
        self.assert_(isinstance(result.custom, MyWidget))
        self.assert_(isinstance(result.custom2, MyWidget))
        self.assert_(result.custom.isPython())

if __name__ == '__main__':
    unittest.main()


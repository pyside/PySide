import unittest
import os
from helper import UsesQApplication

from PySide import QtCore, QtGui
from PySide.QtUiTools import QUiLoader

class MyQUiLoader(QUiLoader):
    def __init__(self, baseinstance):
        QUiLoader.__init__(self)
        self.baseinstance = baseinstance
        self._widgets = []

    def createWidget(self, className, parent=None, name=""):
        widget = QUiLoader.createWidget(self, className, parent, name)
        self._widgets.append(widget)
        if parent is None:
            return self.baseinstance
        else:
            setattr(self.baseinstance, name, widget)
            return widget

class ButTest(UsesQApplication):
    def testCase(self):
        w = QtGui.QWidget()
        loader = MyQUiLoader(w)

        filePath = os.path.join(os.path.dirname(__file__), 'minimal.ui')
        ui = loader.load(filePath)

        self.assertEqual(len(loader._widgets), 1)
        self.assertEqual(type(loader._widgets[0]), QtGui.QFrame)

if __name__ == '__main__':
    unittest.main()


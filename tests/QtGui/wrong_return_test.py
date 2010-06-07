'''Test cases for Virtual functions with wrong return type'''

import unittest

from PySide import QtCore, QtGui

from helper import UsesQApplication

class MyWidget(QtGui.QWidget):
    def __init__(self, parent=None):
        super(MyWidget, self).__init__(parent)

    def sizeHint(self):
        pass

class testCase(UsesQApplication):

    def testVirtualReturn(self):
        w = MyWidget()
        self.assertRaises(TypeError, w.show)

if __name__ == '__main__':
    unittest.main()

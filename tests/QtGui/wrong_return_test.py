'''Test cases for Virtual functions with wrong return type'''

import unittest
import py3kcompat as py3k
from PySide import QtGui
from helper import UsesQApplication

import warnings
warnings.simplefilter('error')


class MyWidget(QtGui.QWidget):
    def __init__(self, parent=None):
        super(MyWidget, self).__init__(parent)

    def sizeHint(self):
        pass

class testCase(UsesQApplication):

    def testVirtualReturn(self):
        w = MyWidget()
        if py3k.IS_PY3K:
            self.assertWarns(RuntimeWarning, w.show)
        else:
            self.assertRaises(RuntimeWarning, w.show)


if __name__ == '__main__':
    unittest.main()

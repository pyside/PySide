import unittest
from PySide.QtCore import *
from PySide.QtGui import *

def foo(a, b):
    pass

class TestBug941 (unittest.TestCase):

    def testIt(self):
        app = QApplication([])
        view = QHeaderView(Qt.Horizontal)
        self.assertTrue(view.sortIndicatorChanged.connect(foo))
        view.sortIndicatorChanged.emit(0, Qt.Vertical) # this can't raise an exception!

if __name__ == '__main__':
    unittest.main()

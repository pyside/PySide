
import unittest

from PySide.QtCore import QObject, QTimer, QThread
from PySide.QtGui import *

class Foo(QTableView):
    def __init__(self, parent=None):
        QTableView.__init__(self, parent)

from helper import UsesQApplication

class TestParentType(UsesQApplication):

    def testParentType(self):
        # Test the problem with calling QObject.parent from a QWidget
        # when the parent is a python class derived from a QWidget-derived
        # class. The method was returning the last C++ class in the hierarchy
        parent = Foo()
        w2 = QWidget(parent)
        self.assert_(isinstance(w2.parentWidget(), Foo))
        self.assert_(isinstance(w2.parent(), Foo))

if __name__ == '__main__':
    unittest.main()

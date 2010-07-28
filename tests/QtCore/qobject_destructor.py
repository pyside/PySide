import sys
import unittest
from PySide import QtCore

class MyObject(QtCore.QObject):
    def __init__(self, other=None):
        QtCore.QObject.__init__(self, None)
        self._o = other

class TestDestructor(unittest.TestCase):
    def testReference(self):
        o = QtCore.QObject()
        m = MyObject(o)
        self.assertEqual(sys.getrefcount(o), 3)
        del m
        self.assertEqual(sys.getrefcount(o), 2)

if __name__ == '__main__':
    unittest.main()

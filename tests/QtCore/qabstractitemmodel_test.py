# -*- coding: utf-8 -*-

import unittest
from PySide.QtCore import *

class MyModel (QAbstractListModel):
    pass

class Foo:
    pass

class TestQModelIndexInternalPointer(unittest.TestCase):

    def testInternalPointer(self):
        m = MyModel()
        foo = Foo()
        idx = m.createIndex(0,0, foo)

if __name__ == '__main__':
    unittest.main()


# -*- coding: utf-8 -*-

''' Test case for QAbstractListModel.createIndex and QModelIndex.internalPointer'''

import sys
import unittest
from PySide.QtCore import *

class MyModel (QAbstractListModel):
    pass

class TestQModelIndexInternalPointer(unittest.TestCase):
    ''' Test case for QAbstractListModel.createIndex and QModelIndex.internalPointer'''

    def setUp(self):
        #Acquire resources
        self.model = MyModel()

    def tearDown(self):
        #Release resources
        del self.model

    def testInternalPointer(self):
        #Test QAbstractListModel.createIndex and
        #QModelIndex.internalPointer with regular
        #Python objects
        idx = self.model.createIndex(0, 0, "Hello")
        self.assertEqual("Hello", idx.internalPointer())
        a = [1, 2, 3]
        idx = self.model.createIndex(0, 0, a)
        self.assertEqual(a, idx.internalPointer())

    def testReferenceCounting(self):
        #Test reference counting when retrieving data with
        #QModelIndex.internalPointer
        a = [1, 2, 3]
        a_refcnt = sys.getrefcount(a)
        idx = self.model.createIndex(0, 0, a)
        ptr = idx.internalPointer()
        self.assertEqual(sys.getrefcount(a), a_refcnt + 1)

    def testIndexForDefaultDataArg(self):
        #Test QAbstractListModel.createIndex with a default
        #value for data argument
        idx = self.model.createIndex(0, 0)
        self.assertEqual(None, idx.internalPointer())

if __name__ == '__main__':
    unittest.main()


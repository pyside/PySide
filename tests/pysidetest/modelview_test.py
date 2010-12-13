#!/usr/bin/python

import unittest
from testbinding import TestView
from PySide.QtCore import QAbstractListModel, QObject, QModelIndex

'''Tests model/view relationship.'''

object_name = 'test object'

class MyObject(QObject):
    pass

class ListModelKeepsReference(QAbstractListModel):
    def rowCount(self, parent=QModelIndex()):
        return 1

    def data(self, index, role):
        self.obj = MyObject()
        self.obj.setObjectName(object_name)
        return self.obj

class ListModelDoesntKeepsReference(QAbstractListModel):
    def rowCount(self, parent=QModelIndex()):
        return 1

    def data(self, index, role):
        obj = MyObject()
        obj.setObjectName(object_name)
        return obj

class ModelViewTest(unittest.TestCase):

    def testListModelKeepsReference(self):
        model = ListModelKeepsReference()
        view = TestView(model)
        obj = view.getData()
        self.assertEqual(type(obj), MyObject)
        self.assertEqual(obj.objectName(), object_name)

    def testListModelDoesntKeepsReference(self):
        model = ListModelDoesntKeepsReference()
        view = TestView(model)
        obj = view.getData()
        self.assertEqual(type(obj), MyObject)
        self.assertEqual(obj.objectName(), object_name)


if __name__ == '__main__':
    unittest.main()


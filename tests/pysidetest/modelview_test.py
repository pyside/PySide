#!/usr/bin/python

import unittest
from testbinding import TestView
from PySide.QtCore import QAbstractListModel, QObject, QModelIndex

'''Tests model/view relationship.'''

object_name = 'test object'

class MyObject(QObject):
    pass

class ListModelKeepsReference(QAbstractListModel):
    def __init__(self, parent=None):
        QAbstractListModel.__init__(self, parent)
        self.obj = MyObject()
        self.obj.setObjectName(object_name)

    def rowCount(self, parent=QModelIndex()):
        return 1

    def data(self, index, role):
        return self.obj

class ListModelDoesntKeepsReference(QAbstractListModel):
    def rowCount(self, parent=QModelIndex()):
        return 1

    def data(self, index, role):
        obj = MyObject()
        obj.setObjectName(object_name)
        return obj

class ListModelThatReturnsString(QAbstractListModel):
    def rowCount(self, parent=QModelIndex()):
        return 1

    def data(self, index, role):
        self.obj = 'string'
        return self.obj
        #return 'string'


class ModelViewTest(unittest.TestCase):

    def testListModelDoesntKeepsReference(self):
        model = ListModelDoesntKeepsReference()
        view = TestView(model)
        obj = view.getData()
        self.assertEqual(type(obj), QObject)
        self.assertEqual(obj.objectName(), object_name)

    def testListModelKeepsReference(self):
        model = ListModelKeepsReference()
        view = TestView(model)
        obj = view.getData()
        self.assertEqual(type(obj), MyObject)
        self.assertEqual(obj.objectName(), object_name)

    def testListModelThatReturnsString(self):
        model = ListModelThatReturnsString()
        view = TestView(model)
        obj = view.getData()
        self.assertEqual(type(obj), unicode)
        self.assertEqual(obj, 'string')

if __name__ == '__main__':
    unittest.main()


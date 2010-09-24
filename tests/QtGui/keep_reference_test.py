#!/usr/bin/env python

import unittest

from sys import getrefcount
from helper import UsesQApplication
from PySide.QtCore import *
from PySide.QtGui import QTableView

class TestModel(QAbstractTableModel):
    def __init__(self, parent=None):
        QAbstractTableModel.__init__(self, parent)
    def rowCount(self, parent):
        return 0
    def columnCount(self, parent):
        return 0
    def data(self, index, role):
        return None

class KeepReferenceTest(UsesQApplication):

    def testModelWithoutParent(self):
        view = QTableView()
        model = TestModel()
        view.setModel(model)
        samemodel = view.model()
        self.assertEqual(model, samemodel)

    def testModelWithParent(self):
        view = QTableView()
        model = TestModel(None)
        view.setModel(model)
        samemodel = view.model()
        self.assertEqual(model, samemodel)

    def testReferenceCounting(self):
        '''Tests reference count of model object referred by view objects.'''
        model1 = TestModel()
        refcount1 = getrefcount(model1)
        view1 = QTableView()
        view1.setModel(model1)
        self.assertEqual(getrefcount(view1.model()), refcount1 + 1)

        view2 = QTableView()
        view2.setModel(model1)
        self.assertEqual(getrefcount(view2.model()), refcount1 + 2)

        model2 = TestModel()
        view2.setModel(model2)
        self.assertEqual(getrefcount(view1.model()), refcount1 + 1)

    def testReferenceCountingWhenDeletingReferrer(self):
        '''Tests reference count of model object referred by deceased view object.'''
        model = TestModel()
        refcount1 = getrefcount(model)
        view = QTableView()
        view.setModel(model)
        self.assertEqual(getrefcount(view.model()), refcount1 + 1)

        del view
        self.assertEqual(getrefcount(model), refcount1)

    def testReferreedObjectSurvivalAfterContextEnd(self):
        '''Model object assigned to a view object must survive after getting out of context.'''
        def createModelAndSetToView(view):
            model = TestModel()
            model.setObjectName('created model')
            view.setModel(model)
        view = QTableView()
        createModelAndSetToView(view)
        model = view.model()

if __name__ == '__main__':
    unittest.main()


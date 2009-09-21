#!/usr/bin/env python

import unittest

from helper import UsesQApplication
from PySide.QtCore import QAbstractTableModel, QVariant
from PySide.QtGui import QTableView

class TestModel(QAbstractTableModel):
    def __init__(self, parent=None):
        QAbstractTableModel.__init__(self, parent)
    def rowCount(self, parent):
        return 0
    def columnCount(self, parent):
        return 0
    def data(self, index, role):
        return QVariant()

class ParentPolicyTest(UsesQApplication):

    def testModelWithoutParent(self):
        view = QTableView()
        model = TestModel()
        view.setModel(model)
        samemodel = view.model()
        self.assertEqual(model, samemodel)

    def testModelWithParent(self):
        view = QTableView()
        model = TestModel(self.app)
        view.setModel(model)
        samemodel = view.model()
        self.assertEqual(model, samemodel)

if __name__ == '__main__':
    unittest.main()


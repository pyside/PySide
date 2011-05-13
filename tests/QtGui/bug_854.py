from PySide.QtGui import QTableView, QVBoxLayout, QApplication
from PySide.QtCore import QAbstractItemModel

from helper import UsesQApplication
import unittest


class VirtualList(QAbstractItemModel):
    def __getitem__(self, index):
        self._getItemCalled = True
        pass

    def rowCount(self, parent):
        return 5000

    def columnCount(self, parent):
        return 3

    def index(self, row, column, parent):
        return self.createIndex(row, column)

    def parent(self, index):
         return QModelIndex()

    def data(self, index, role):
        return "(%i, %i)" % (index.row(), index.column())


class TestQAbstractItemModel(UsesQApplication):
    def testSetModel(self):
        model = VirtualList()
        model._getItemCalled = False
        table = QTableView()
        table.setModel(model)
        table.show()
        self.assertFalse(model._getItemCalled)

if __name__ == "__main__":
    unittest.main()


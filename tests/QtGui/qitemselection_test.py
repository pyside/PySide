import unittest

from helper import UsesQApplication
from PySide.QtGui import QItemSelection, QStandardItemModel

class QItemSelectionTest(UsesQApplication):
    def testLen(self):
        model = QStandardItemModel(2, 2)
        model.insertRow(0)
        model.insertRow(1)
        model.insertColumn(0)
        model.insertColumn(1)
        selection = QItemSelection(model.index(0,0), model.index(1,1))
        self.assertEqual(len(selection), 1)

if __name__ == '__main__':
    unittest.main()


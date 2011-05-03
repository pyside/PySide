import sys

import unittest
from PySide.QtGui import QApplication, QStandardItemModel, QStandardItem, QItemSelection

class Bug324(unittest.TestCase):
    def testOperators(self):
        model = QStandardItemModel()
        for i in range(100):
            model.appendRow(QStandardItem("Item: %d"%i))

        first = model.index(0, 0)
        second = model.index(10, 0)
        third = model.index(20, 0)
        fourth = model.index(30, 0)

        sel = QItemSelection(first, second)
        sel2 = QItemSelection()
        sel2.select(third, fourth)

        sel3 = sel + sel2 #check operator +
        self.assertEqual(len(sel3), 2)
        sel4 = sel
        sel4 += sel2 #check operator +=
        self.assertEqual(len(sel4), 2)
        self.assertEqual(sel4, sel3)

if __name__ == "__main__":
    unittest.main()

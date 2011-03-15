import unittest

from PySide.QtCore import *

class MyModel (QAbstractListModel):
    def rowCount(self, parent = None):
        return 3

class TestBug706(unittest.TestCase):

    def mySlot(self, idx, start, end):
        self.start = start
        self.end = end

    def testIt(self):
        self.start = None
        self.end = None

        app = QCoreApplication([])
        model = MyModel()
        model.columnsAboutToBeInserted.connect(self.mySlot)
        model.columnsAboutToBeInserted.emit(QModelIndex(), 0, 1)
        self.assertEqual(self.start, 0)
        self.assertEqual(self.end, 1)

if __name__ == '__main__':
    unittest.main()

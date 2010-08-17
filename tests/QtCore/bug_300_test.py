from PySide.QtGui import QStringListModel
from PySide.QtCore import QModelIndex
import unittest

class TestQAbstractItemModelSignals(unittest.TestCase):
    def sigCallback(self, index, r, c):
        self._called = True

    def testSignals(self):
        self._called = False
        m = QStringListModel()
        m.rowsAboutToBeInserted[QModelIndex,int,int].connect(self.sigCallback)
        m.insertRows(0, 3)
        self.assert_(self._called)

if __name__ == '__main__':
    unittest.main()

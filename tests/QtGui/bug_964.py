import unittest
from PySide.QtCore import *
from PySide.QtGui import *

class TestBug964 (unittest.TestCase):

    def testIt(self):
        app = QApplication([])
        model = QStringListModel(["1", "2"])
        view = QListView()
        view.setModel(model)
        view.setCurrentIndex(model.index(0,0))
        newCursor = view.moveCursor(QAbstractItemView.MoveDown, Qt.NoModifier)
        self.assertEqual(newCursor.row(), 1)
        self.assertEqual(newCursor.column(), 0)

if __name__ == "__main__":
    unittest.main()


from PySide.QtCore import *
from PySide.QtGui import *
import unittest

class MyModel (QAbstractListModel):

    stupidLine = QLine(0, 0, 10, 10)

    def rowCount(self, parent):
        return 1

    def data(self, index, role):
        return self.stupidLine

class TestBug693(unittest.TestCase):
    def testIt(self):
        app = QApplication([])
        model = MyModel()
        view = QListView()
        view.setModel(model)
        view.show()

        # This must NOT throw the exception:
        # RuntimeError: Internal C++ object (PySide.QtCore.QLine) already deleted.
        MyModel.stupidLine.isNull()



if __name__ == "__main__":
    unittest.main()

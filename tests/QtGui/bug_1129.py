''' unit test for BUG #1129 '''
''' See http://bugs.pyside.org/show_bug.cgi?id=1129. '''

from PySide import QtCore, QtGui
from helper import UsesQApplication
import unittest

class Item(QtGui.QStandardItem):
    def data(self, role):
        if role == QtCore.Qt.DisplayRole:
            return str(self.model())

        return super(Item, self).data(role)

class Window(QtGui.QMainWindow):
    def __init__(self, parent=None):
        super(Window, self).__init__(parent)

        model = QtGui.QStandardItemModel(1, 1, self)
        model.setItem(0, 0, Item())

        self.setCentralWidget(QtGui.QTreeView(self))
        self.centralWidget().setModel(model)

        QtCore.QTimer.singleShot(0, self.raise_)

class QStandardItemTestCase(UsesQApplication):
    def testDataFunction(self):
        w = Window()
        w.show()

if __name__ == "__main__":
    unittest.main()

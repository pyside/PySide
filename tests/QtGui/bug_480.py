import unittest

from PySide import QtGui

class BuggyWidget(QtGui.QWidget):
    def setup(self):
        self.verticalLayout = QtGui.QVBoxLayout(self)
        self.gridLayout = QtGui.QGridLayout()
        self.lbl = QtGui.QLabel(self)
        self.gridLayout.addWidget(self.lbl, 0, 1, 1, 1)

        # this cause a segfault during the ownership transfer
        self.verticalLayout.addLayout(self.gridLayout)

class LayoutTransferOwnerShip(unittest.TestCase):
    def testBug(self):
        app = QtGui.QApplication([])
        w = BuggyWidget()
        w.setup()
        w.show()
        self.assert_(True)

if __name__ == '__main__':
    unittest.main()


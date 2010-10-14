
import unittest

import sys
from PySide import QtGui, QtCore
from helper import UsesQApplication

class QListWidgetTest(UsesQApplication):

    def populateList(self, lst):
        o = QtCore.QObject()
        o.setObjectName("obj")

        item = QtGui.QListWidgetItem("item0")
        item.setData(QtCore.Qt.UserRole, o)
        #item._data = o
        self.assert_(sys.getrefcount(o), 3)
        self.assert_(sys.getrefcount(item), 2)
        lst.addItem(item)
        self.assert_(sys.getrefcount(item), 3)

    def checkCurrentItem(self, lst):
        item = lst.currentItem()
        self.assert_(sys.getrefcount(item), 3)

    def checkItemData(self, lst):
        item = lst.currentItem()
        o = item.data(QtCore.Qt.UserRole)
        self.assert_(sys.getrefcount(o), 4)
        self.assertEqual(o, item._data)
        self.assert_(sys.getrefcount(o), 2)

    def testConstructorWithParent(self):
        lst = QtGui.QListWidget()
        self.populateList(lst)
        self.checkCurrentItem(lst)
        i = lst.item(0)
        self.assert_(sys.getrefcount(i), 3)

        del lst
        self.assert_(sys.getrefcount(i), 2)
        del i

    def testIt(self):
        lst = QtGui.QListWidget()
        lst.show()
        slot = lambda : lst.removeItemWidget(lst.currentItem())
        lst.addItem(QtGui.QListWidgetItem("foo"))
        QtCore.QTimer.singleShot(0, slot)
        QtCore.QTimer.singleShot(0, lst.close)
        self.app.exec_()
        self.assertEqual(lst.count(), 1)

if __name__ == '__main__':
    unittest.main()

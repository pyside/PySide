""" Unittest for bug #547 """
""" http://bugs.openbossa.org/show_bug.cgi?id=547 """

from PySide import QtGui
import sys
import unittest

class MyMainWindow(unittest.TestCase):
    app = QtGui.QApplication(sys.argv)
    def testCase1(self):
        self._tree = QtGui.QTreeWidget()
        self._tree.setColumnCount(2)
        self._i1 = None
        self._i11 = None

        self._updateTree()
        self.assertEqual(sys.getrefcount(self._i1), 3)
        self.assertEqual(sys.getrefcount(self._i11), 3)

        self._i11.parent().setExpanded(True)
        self._i11.setExpanded(True)

        self._updateTree()
        self.assertEqual(sys.getrefcount(self._i1), 3)
        self.assertEqual(sys.getrefcount(self._i11), 3)

    def testCase2(self):
        self._tree = QtGui.QTreeWidget()
        self._tree.setColumnCount(2)
        self._i1 = None
        self._i11 = None

        self._updateTree()
        self.assertEqual(sys.getrefcount(self._i1), 3)
        self.assertEqual(sys.getrefcount(self._i11), 3)

        self._i11.parent().setExpanded(True)
        self._i11.setExpanded(True)

        self.assertEqual(sys.getrefcount(self._i1), 3)
        self.assertEqual(sys.getrefcount(self._i11), 3)

    def _updateTree(self):
        self._tree.clear()
        if self._i1 and self._i11:
            self.assertEqual(sys.getrefcount(self._i1), 2)
            self.assertEqual(sys.getrefcount(self._i11), 2)

        self._i1 = QtGui.QTreeWidgetItem(self._tree, ['1', ])
        self.assertEqual(sys.getrefcount(self._i1), 3)
        self._i11 = QtGui.QTreeWidgetItem(self._i1, ['11', ])
        self.assertEqual(sys.getrefcount(self._i11), 3)

if __name__ == '__main__':
    unittest.main()


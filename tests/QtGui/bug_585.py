'''Test bug 585: http://bugs.openbossa.org/show_bug.cgi?id=585'''

from PySide import QtCore ,QtGui
import sys
import unittest


class Bug585(unittest.TestCase):
    def testCase(self):
        app = QtGui.QApplication([])
        self._tree = QtGui.QTreeWidget()
        self._tree.setColumnCount(2)
        i1 = QtGui.QTreeWidgetItem(self._tree, ['1', ])
        i2 = QtGui.QTreeWidgetItem(self._tree, ['2', ])
        refCount = sys.getrefcount(i1)

        # this function return None
        # because the topLevelItem does not has a parent item
        # but still have a TreeWidget as a parent
        self._tree.topLevelItem(0).parent()

        self.assertEqual(refCount, sys.getrefcount(i1))

if __name__ == '__main__':
    unittest.main()


import unittest
import sys

from PySide.QtGui import QStandardItemModel, QWidget, QStandardItem
import shiboken

from helper import UsesQApplication

class QStandardItemModelTest(UsesQApplication):

    def setUp(self):
       super(QStandardItemModelTest, self).setUp()
       self.window = QWidget()
       self.model = QStandardItemModel(0, 3, self.window)

    def tearDown(self):
       del self.window
       del self.model
       super(QStandardItemModelTest, self).tearDown()

    def testInsertRow(self):
        # bug #227
        self.model.insertRow(0)

    def testClear(self):

        model = QStandardItemModel()
        root = model.invisibleRootItem()
        model.clear()
        self.assertFalse(shiboken.isValid(root))


class QStandardItemModelRef(UsesQApplication):
    def testRefCount(self):
        model = QStandardItemModel(5, 5)
        items = []
        for r in range(5):
            row = []
            for c in range(5):
                row.append(QStandardItem("%d,%d" % (r,c)) )
                self.assertEqual(sys.getrefcount(row[c]), 2)

            model.insertRow(r, row)

            for c in range(5):
                ref_after = sys.getrefcount(row[c])
                # check if the ref count was incremented after insertRow
                self.assertEqual(ref_after, 3)

            items.append(row)
            row = None

        for r in range(3):
            my_row = model.takeRow(0)
            my_row = None
            for c in range(5):
                # only rest 1 reference
                self.assertEqual(sys.getrefcount(items[r][c]), 2)

        my_i = model.item(0,0)
        # ref(my_i) + parent_ref + items list ref
        self.assertEqual(sys.getrefcount(my_i), 4)

        model.clear()
        # ref(my_i)
        self.assertEqual(sys.getrefcount(my_i), 3)


if __name__ == '__main__':
    unittest.main()


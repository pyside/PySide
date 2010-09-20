''' Test bug 367: http://bugs.openbossa.org/show_bug.cgi?id=367'''

import sys
import unittest
from helper import UsesQApplication
from PySide import QtCore,QtGui

class BugTest(UsesQApplication):
    def testCase(self):
        model = QtGui.QStandardItemModel()
        parentItem = model.invisibleRootItem()
        for i in range(10):
            item = QtGui.QStandardItem()
            rcount =  sys.getrefcount(item)
            parentItem.appendRow(item)
            self.assertEqual(rcount+1, sys.getrefcount(item))
            parentItem = item

        self.assert_(True)

if __name__ == '__main__':
    unittest.main()

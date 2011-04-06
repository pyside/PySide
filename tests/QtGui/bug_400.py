''' Test bug 400: http://bugs.openbossa.org/show_bug.cgi?id=400'''

import unittest
from helper import UsesQApplication
from PySide.QtGui import QTreeWidgetItemIterator, QTreeWidgetItem, QTreeWidget

class BugTest(UsesQApplication):
    def testCase(self):
        treeWidget = QTreeWidget()
        treeWidget.setColumnCount(1)
        items = []
        for i in range(10):
            items.append(QTreeWidgetItem(None, ["item: %i" % i]))

        treeWidget.insertTopLevelItems(0, items);
        _iter = QTreeWidgetItemIterator(treeWidget)
        index = 0
        while(_iter.value()):
            item = _iter.value()
            self.assert_(item is items[index])
            index += 1
            _iter += 1


if __name__ == '__main__':
    unittest.main()

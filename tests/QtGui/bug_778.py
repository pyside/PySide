import unittest

from helper import UsesQApplication

from PySide.QtGui import QTreeWidget, QTreeWidgetItem, QTreeWidgetItemIterator

class QTreeWidgetItemIteratorTest(UsesQApplication):
    def testWidgetIterator(self):
        treeWidget = QTreeWidget()
        treeWidget.setColumnCount(1)
        items = []
        for i in range(10):
            items.append(QTreeWidgetItem(None, ['item: %d' % i]))
        treeWidget.insertTopLevelItems(0, items)

        index = 0
        for it in QTreeWidgetItemIterator(treeWidget):
            self.assertEqual(it.value().text(0), 'item: %d' % index)
            index += 1

if __name__ == '__main__':
    unittest.main()

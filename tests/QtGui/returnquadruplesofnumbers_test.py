import unittest
from PySide.QtGui import QLayout, QWidget, QGraphicsLayout, QGraphicsLayoutItem, QTextCursor, QPrinter

from helper import UsesQApplication

class Layout(QLayout):
    def __init__(self):
        QLayout.__init__(self)

class GraphicsLayout(QGraphicsLayout):
    def __init__(self):
        QGraphicsLayout.__init__(self)

class GraphicsLayoutItem(QGraphicsLayoutItem):
    def __init__(self):
        QGraphicsLayoutItem.__init__(self)

class ReturnsQuadruplesOfNumbers(UsesQApplication):
    def compareTuples(self, ta, tb):
        for va,vb in zip(ta, tb):
            if round(va) != round(vb):
                return False
        return True

    def testQGraphicsLayoutGetContentsMargins(self):
        obj = GraphicsLayout()
        values = (10.0, 20.0, 30.0, 40.0)
        obj.setContentsMargins(*values)
        self.assert_(self.compareTuples(obj.getContentsMargins(), values))

    def testQGraphicsLayoutItemGetContentsMargins(self):
        obj = GraphicsLayoutItem()
        self.assert_(self.compareTuples(obj.getContentsMargins(), (0.0, 0.0, 0.0, 0.0)))

    def testQWidgetGetContentsMargins(self):
        obj = QWidget()
        values = (10, 20, 30, 40)
        obj.setContentsMargins(*values)
        self.assert_(self.compareTuples(obj.getContentsMargins(), values))

    def testQLayoutGetContentsMargins(self):
        obj = Layout()
        values = (10, 20, 30, 40)
        obj.setContentsMargins(*values)
        self.assert_(self.compareTuples(obj.getContentsMargins(), values))

    def testQTextCursorSelectedTableCells(self):
        obj = QTextCursor()
        self.assertEquals(obj.selectedTableCells(), (-1, -1, -1, -1))

    def testQPrinterGetPageMargins(self):
        # Bug #742
        obj = QPrinter()
        values = (10.0, 20.0, 30.0, 40.0, QPrinter.Point)
        obj.setPageMargins(*values)
        self.assert_(self.compareTuples(obj.getPageMargins(QPrinter.Point), values[:-1]))

if __name__ == "__main__":
   unittest.main()


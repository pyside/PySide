#!/usr/bin/python

import unittest

from PySide.QtGui import QGraphicsScene, QGraphicsRectItem, QGraphicsView, QApplication, QBrush, QColor
from PySide.QtCore import QTimer
from helper import UsesQApplication

qgraphics_item_painted = False

class RoundRectItem(QGraphicsRectItem):

    def __init__(self, x, y, w, h):
        QGraphicsRectItem.__init__(self, x, y, w, h)

    def paint(self, painter, qstyleoptiongraphicsitem, qwidget):
        global qgraphics_item_painted
        qgraphics_item_painted = True


class QGraphicsItemTest(UsesQApplication):

    def createRoundRect(self, scene):
        item = RoundRectItem(10, 10, 100, 100)
        item.setBrush(QBrush(QColor(255, 0, 0)))
        scene.addItem(item)
        return item

    def quit_app(self):
        self.app.quit()

    def test_setParentItem(self):
        global qgraphics_item_painted

        scene = QGraphicsScene()
        scene.addText("test")
        view = QGraphicsView(scene)

        rect = self.createRoundRect(scene)
        view.show()
        QTimer.singleShot(1000, self.quit_app)
        self.app.exec_()
        self.assert_(qgraphics_item_painted)


if __name__ == '__main__':
    unittest.main()


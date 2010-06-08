import unittest

from helper import UsesQApplication
from PySide.QtCore import Qt, QTimer
from PySide.QtGui import QLabel, QPainter
from PySide.QtGui import QGraphicsScene, QGraphicsView, QGraphicsItem, QGraphicsProxyWidget

class CustomProxy(QGraphicsProxyWidget):
    def __init__(self, parent=None, wFlags=0):
        QGraphicsProxyWidget.__init__(self, parent, wFlags)

class CustomProxyWidgetTest(UsesQApplication):
    def testCustomProxyWidget(self):
        scene = QGraphicsScene()

        proxy = CustomProxy(None, Qt.Window)
        widget = QLabel('Widget')
        proxy.setWidget(widget)
        proxy.setCacheMode(QGraphicsItem.DeviceCoordinateCache)
        scene.addItem(proxy)
        scene.setSceneRect(scene.itemsBoundingRect())

        view = QGraphicsView(scene)
        view.setRenderHints(QPainter.Antialiasing|QPainter.SmoothPixmapTransform)
        view.setViewportUpdateMode(QGraphicsView.BoundingRectViewportUpdate)
        view.show()

        timer = QTimer.singleShot(100, self.app.quit)
        self.app.exec_()

if __name__ == '__main__':
    unittest.main()


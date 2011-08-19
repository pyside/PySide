import unittest
from PySide.QtCore import QSizeF
from PySide.QtGui import QGraphicsProxyWidget, QSizePolicy, QPushButton, QGraphicsScene, QGraphicsView

from helper import TimedQApplication

def createItem(minimum, preferred, maximum, name):
    w = QGraphicsProxyWidget()

    w.setWidget(QPushButton(name))
    w.setMinimumSize(minimum)
    w.setPreferredSize(preferred)
    w.setMaximumSize(maximum)
    w.setSizePolicy(QSizePolicy.Preferred, QSizePolicy.Preferred)

    return w

class TestBug972 (TimedQApplication):

    # Test if the function QGraphicsProxyWidget.setWidget have the correct behavior
    def testIt(self):
        scene = QGraphicsScene()

        minSize = QSizeF(30, 100)
        prefSize = QSizeF(210, 100)
        maxSize = QSizeF(300, 100)

        a = createItem(minSize, prefSize, maxSize, "A")
        b = createItem(minSize, prefSize, maxSize, "B")
        c = createItem(minSize, prefSize, maxSize, "C")
        d = createItem(minSize, prefSize, maxSize, "D")

        view = QGraphicsView(scene)
        view.show()
        self.app.exec_()


if __name__ == "__main__":
    unittest.main()

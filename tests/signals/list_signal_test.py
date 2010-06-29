# -*- coding: utf-8 -*-

import unittest

from PySide.QtCore import *
from PySide.QtGui import *

class ListConnectionTest(unittest.TestCase):

    def modifyScene(self):
        self.scene.addLine(0, 0, 10, 10)

    def sceneChanged(self, rects):
        # Qt isn't so cute and sends this signal with empty lists and null rects sometimes.
        if len(rects) > 0 and not rects[0].isNull():
            self.rects = rects
            QApplication.quit()

    def testConnection(self):
        app = QApplication([])

        self.scene = QGraphicsScene()
        QTimer.singleShot(0, self.modifyScene)
        self.scene.changed.connect(self.sceneChanged)

        app.exec_()
        self.assertEquals(len(self.rects), 1)
        self.assertEquals(self.rects[0].x(), 0)
        self.assertEquals(self.rects[0].y(), 0)
        self.assertEquals(self.rects[0].width(), 10)
        self.assertEquals(self.rects[0].height(), 10)

if __name__ == '__main__':
    unittest.main()


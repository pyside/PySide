import unittest

import os
from helper import UsesQApplication
from PySide.QtCore import QTimer
from PySide.QtGui import QPicture, QPainter, QWidget

class MyWidget(QWidget):
    def paintEvent(self, e):
        p = QPainter(self)
        p.drawPicture(0, 0, self._picture)
        self._app.quit()

class QPictureTest(UsesQApplication):
    def testFromData(self):
        picture = QPicture()
        painter = QPainter()
        painter.begin(picture)
        painter.drawEllipse(10,20, 80,70)
        painter.end()

        data = picture.data()
        picture2 = QPicture()
        picture2.setData(data)

        self.assertEqual(picture2.data(), picture.data())

        w = MyWidget()
        w._picture = picture2
        w._app = self.app

        QTimer.singleShot(300, w.show)
        self.app.exec_()

if __name__ == '__main__':
    unittest.main()


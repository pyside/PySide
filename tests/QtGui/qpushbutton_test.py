import unittest

from helper import UsesQApplication
from PySide.QtGui import QPushButton, QMenu, QWidget
from PySide.QtCore import QTimer

class MyWidget(QWidget):
    def __init__(self):
        QWidget.__init__(self)

        m = QMenu(self)
        b = QPushButton("Hello", self)
        b.setMenu(m)


class QPushButtonTest(UsesQApplication):
    def createMenu(self, button):
        m = QMenu()
        button.setMenu(m)

    def testSetMenu(self):
        w = MyWidget()
        w.show()

        timer = QTimer.singleShot(100, self.app.quit)
        self.app.exec_()

if __name__ == '__main__':
    unittest.main()


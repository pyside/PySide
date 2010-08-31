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

    def buttonCb(self, checked):
        self._clicked = True

    def testBoolinSignal(self):
        b = QPushButton()
        b.setCheckable(True)
        self._clicked = False
        b.toggled[bool].connect(self.buttonCb)
        b.toggle()
        self.assert_(self._clicked)

if __name__ == '__main__':
    unittest.main()


import unittest
from PySide.QtCore import *

class MyTimer (QTimer):
    def __init__(self):
        QTimer.__init__(self)
        self.startCalled = False

    @Slot()
    def slotUsedToIncreaseMethodOffset(self):
        pass

class MyTimer2 (MyTimer):

    @Slot()
    def slotUsedToIncreaseMethodOffset2(self):
        pass

    def start(self):
        self.startCalled = True
        QCoreApplication.instance().quit()

class TestBug1019 (unittest.TestCase):
    def testIt(self):
        app = QCoreApplication([])
        t = MyTimer2()
        QTimer.singleShot(0, t.start)
        app.exec_()
        self.assertTrue(t.startCalled)

if __name__ == "__main__":
    unittest.main()

import unittest

from PySide.QtGui import *

class TestBug549(unittest.TestCase):
    def testBug(self):
        app = QApplication([])
        w = QGraphicsWidget()
        w.setContentsMargins(1, 2, 3, 4)
        self.assertEquals(w.getContentsMargins(), (1, 2, 3, 4))
        w.setWindowFrameMargins(5, 6, 7, 8)
        self.assertEquals(w.getWindowFrameMargins(), (5, 6, 7, 8))

if __name__ == '__main__':
    unittest.main()


import unittest
import sys
from PySide.QtGui import QLabel, QApplication, QPixmap

class TestLabelPixmap(unittest.TestCase):
    def testReference(self):
        l = QLabel()
        p = QPixmap()
        l.setPixmap(p) # doesn't increment pixmap ref because this makes a copy
        self.assertEqual(sys.getrefcount(p), 2)

        p = l.pixmap() # this increment the reference because this is an internal pointer
        self.assertEqual(sys.getrefcount(p), 3)

        p2 = l.pixmap()
        self.assertEqual(p, p2)

if __name__ == '__main__':
    app = QApplication([])
    unittest.main()


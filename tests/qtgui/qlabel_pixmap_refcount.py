
'''Test cases for QLabel->pixmap refcount control'''

import unittest
import sys


from helper import UsesQApplication
from PySide.QtGui import QApplication, QLabel, QPixmap

class QLabelTest(UsesQApplication):
    '''Test case for constructor of QBrush'''

    def testDestroyOwner(self):
        p = QPixmap()
        l = QLabel()
        l.setPixmap(p)

        del p

        p1 = l.pixmap()
        self.assertEqual(sys.getrefcount(p1), 2)
        self.assertEqual(sys.getrefcount(l), 2)

        del l
        self.assertEqual(sys.getrefcount(p1), 2)


    def testRefCount(self):
        p = QPixmap()
        l = QLabel()
        l.setPixmap(p)

        del p

        p1 = l.pixmap()
        self.assertEqual(sys.getrefcount(p1), 2)

        p2 = l.pixmap()
        self.assertEqual(sys.getrefcount(p2), 3)

        p3 = l.pixmap()
        self.assertEqual(sys.getrefcount(p3), 4)

if __name__ == '__main__':
    unittest.main()

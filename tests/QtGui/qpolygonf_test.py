
import unittest
from PySide.QtCore import *
from PySide.QtGui import *

class QPolygonFNotIterableTest(unittest.TestCase):
    """Test if a QPolygonF is iterable"""
    def testIt(self):
        p = QPolygonF(4)
        self.assertEqual(len(p), 4)

        for i in range(0, 4):
            p[i] = QPointF(float(i), float(i))

        i = 0
        for point in p:
            self.assertEqual(int(point.x()), i)
            self.assertEqual(int(point.y()), i)
            i += 1;

if __name__ == '__main__':
    unittest.main()

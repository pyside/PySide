
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

    def testPolygonShiftOperators(self):
        p = QPolygon()
        self.assertEqual(len(p), 0)
        p << QPoint(10, 20) << QPoint(20, 30) << [QPoint(20, 30), QPoint(40, 50)]
        self.assertEqual(len(p), 4)

if __name__ == '__main__':
    unittest.main()

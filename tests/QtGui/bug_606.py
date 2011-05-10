import unittest

import PySide
from PySide.QtGui import QVector2D, QVector3D, QVector4D
from PySide.QtGui import QColor

class testCases(unittest.TestCase):
    def testQVector2DToTuple(self):
        vec = QVector2D(1, 2)
        self.assertEqual((1, 2), vec.toTuple())

    def testQVector3DToTuple(self):
        vec = QVector3D(1, 2, 3)
        self.assertEqual((1, 2, 3), vec.toTuple())

    def testQVector4DToTuple(self):
        vec = QVector4D(1, 2, 3, 4)
        self.assertEqual((1, 2, 3, 4), vec.toTuple())

    def testQColorToTuple(self):
        c = QColor(0, 0, 255)
        c.setRgb(1, 2, 3)
        self.assertEqual((1, 2, 3, 255), c.toTuple())

if __name__ == '__main__':
    unittest.main()

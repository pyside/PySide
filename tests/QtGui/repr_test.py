
import unittest

import PySide
from PySide.QtCore import QPoint
from PySide.QtGui import QMatrix
from PySide.QtGui import QMatrix2x2, QMatrix2x3, QMatrix2x4
from PySide.QtGui import QMatrix3x2, QMatrix3x3, QMatrix3x4
from PySide.QtGui import QMatrix4x2, QMatrix4x3, QMatrix4x4
from PySide.QtGui import QVector2D, QVector3D, QVector4D
from PySide.QtGui import QColor, QTransform, QKeySequence, QQuaternion
from PySide.QtGui import QPolygon

class ReprCopyHelper:
    def testCopy(self):
        copy = eval(self.original.__repr__())
        self.assert_(copy is not self.original)
        self.assertEqual(copy, self.original)

class QTransformReprCopy(ReprCopyHelper, unittest.TestCase):
    def setUp(self):
        self.original = QTransform(1, 2, 3, 4, 5, 6, 7, 8)

class QKeySequenceReprCopy(ReprCopyHelper, unittest.TestCase):
    def setUp(self):
        self.original = QKeySequence("Ctrl+P")

class QQuaternionReprCopy(ReprCopyHelper, unittest.TestCase):
    def setUp(self):
        self.original = QQuaternion(1, 2, 3, 4)

class QVector2DReprCopy(ReprCopyHelper, unittest.TestCase):
    def setUp(self):
        self.original = QVector2D(1, 2)

class QVector3DReprCopy(ReprCopyHelper, unittest.TestCase):
    def setUp(self):
        self.original = QVector3D(1, 2, 3)

class QVector4DReprCopy(ReprCopyHelper, unittest.TestCase):
    def setUp(self):
        self.original = QVector4D(1, 2, 3, 4)

class QMatrixReprCopy(ReprCopyHelper, unittest.TestCase):
    def setUp(self):
        self.original = QMatrix(1, 2, 3, 4, 5, 6)


# Avoid these tests until get gcc fixed
# Related bug: http://gcc.gnu.org/bugzilla/show_bug.cgi?id=43247
"""
class QMatrix2x2ReprCopy(ReprCopyHelper, unittest.TestCase):
    def setUp(self):
        self.original = QMatrix2x2([1, 2, 3, 4])

class QMatrix2x3ReprCopy(ReprCopyHelper, unittest.TestCase):
    def setUp(self):
        self.original = QMatrix2x3([1, 2, 3, 4, 5, 6])

class QMatrix2x4ReprCopy(ReprCopyHelper, unittest.TestCase):
    def setUp(self):
        self.original = QMatrix2x4([1, 2, 3, 4, 5, 6, 7, 8])

class QMatrix3x2ReprCopy(ReprCopyHelper, unittest.TestCase):
    def setUp(self):
        self.original = QMatrix3x2([1, 2, 3, 4, 5, 6])

class QMatrix3x3ReprCopy(ReprCopyHelper, unittest.TestCase):
    def setUp(self):
        self.original = QMatrix3x3([1, 2, 3, 4, 5, 6, 7, 8, 9])

class QMatrix3x4ReprCopy(ReprCopyHelper, unittest.TestCase):
    def setUp(self):
        self.original = QMatrix3x4([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12])

class QMatrix4x2ReprCopy(ReprCopyHelper, unittest.TestCase):
    def setUp(self):
        self.original = QMatrix4x2([1, 2, 3, 4, 5, 6, 7, 8])

class QMatrix4x3ReprCopy(ReprCopyHelper, unittest.TestCase):
    def setUp(self):
        self.original = QMatrix4x3([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12])

class QMatrix4x4ReprCopy(ReprCopyHelper, unittest.TestCase):
    def setUp(self):
        self.original = QMatrix4x4([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16])
"""

if __name__ == '__main__':
    unittest.main()

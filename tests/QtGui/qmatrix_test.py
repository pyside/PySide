import unittest

from PySide.QtCore import QPoint
from PySide.QtGui import QMatrix, QMatrix4x4


def qpointTimesQMatrix(point, matrix):
    '''As seen in "QPoint QMatrix::map(const QPoint &p) const" C++ implementation.'''
    return QPoint(matrix.m11() * point.x() + matrix.m21() * point.y() + matrix.dx(),
                  matrix.m12() * point.x() + matrix.m22() * point.y() + matrix.dy())

class QMatrixTest(unittest.TestCase):

    def testMatrix(self):
        matrix = QMatrix(11, 12, 21, 22, 100, 200)
        point = QPoint(3, 3)
        self.assertEqual(point * matrix, qpointTimesQMatrix(point, matrix))

    def testMatrixWithWrongType(self):
        matrix = QMatrix(11, 12, 21, 22, 100, 200)
        point = QPoint(3, 3)
        self.assertRaises(TypeError, matrix.__mul__, point)

    def testMatrix4x4(self):
        self.assertRaises(TypeError, QMatrix4x4, [0.0, 1.0, 2.0, 3.0])
        self.assertRaises(TypeError, QMatrix4x4, [0.0, 1.0, 2.0, 'I',
                                                  4.0, 5.0, 6.0, 7.0,
                                                  8.0, 9.0, 'N', 11.0,
                                                  12.0, 'd', 14.0, 'T'])

        my_data = [0.0, 1.0, 2.0, 3.0,
                   4.0, 5.0, 6.0, 7.0,
                   8.0, 9.0, 10.0, 11.0,
                   12.0, 13.0, 14.0, 15.0]
        my_datac = [0.0, 4.0, 8.0, 12.0,
                    1.0, 5.0, 9.0, 13.0,
                    2.0, 6.0, 10.0, 14.0,
                    3.0, 7.0, 11.0, 15.0]

        m = QMatrix4x4(my_data)
        d = m.data()
        self.assert_(my_datac, d)

        d = m.copyDataTo()
        self.assert_(my_data == list(d))

    def testMatrixMapping(self):
        m = QMatrix(1.0, 2.0, 1.0, 3.0, 100.0, 200.0)
        res = m.map(5, 5)
        self.assertAlmostEqual(res[0], 5 * 1.0 + 5 * 1.0 + 100.0)
        self.assertAlmostEqual(res[1], 5 * 2.0 + 5 * 3.0 + 200.0)
        res = m.map(5.0, 5.0)
        self.assertAlmostEqual(res[0], 5.0 * 1.0 + 5.0 * 1.0 + 100.0)
        self.assertAlmostEqual(res[1], 5.0 * 2.0 + 5.0 * 3.0 + 200.0)

if __name__ == '__main__':
    unittest.main()


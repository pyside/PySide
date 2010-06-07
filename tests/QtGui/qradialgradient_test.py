import unittest

from PySide.QtGui import QRadialGradient
from PySide.QtCore import QPointF

class QRadialGradientConstructor(unittest.TestCase):
    def _compare(self, qptf, tpl):
        self.assertEqual((qptf.x(), qptf.y()), tpl)

    def _assertValues(self, grad):
        self._compare(grad.center(), (1.0, 2.0))
        self._compare(grad.focalPoint(), (3.0, 4.0))
        self.assertEqual(grad.radius(), 5.0)

    def testAllInt(self):
        grad = QRadialGradient(1, 2, 5, 3, 4)
        self._assertValues(grad)

    def testQPointF(self):
        grad = QRadialGradient(QPointF(1, 2), 5, QPointF(3, 4))
        self._assertValues(grad)

    def testSetQPointF(self):
        grad = QRadialGradient()
        grad.setCenter(QPointF(1, 2))
        self._compare(grad.center(), (1.0, 2.0))

if __name__ == '__main__':
    unittest.main()

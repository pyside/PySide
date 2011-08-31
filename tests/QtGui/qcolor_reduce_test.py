import unittest
import pickle
from PySide.QtGui import QColor

class TestQColor (unittest.TestCase):
    def reduceColor(self, c):
        p = pickle.dumps(c)
        c2 = pickle.loads(p)
        self.assertEqual(c.spec(), c2.spec())
        self.assertEqual(c, c2)

    def testReduceEmpty(self):
        self.reduceColor(QColor())

    def testReduceString(self):
        self.reduceColor(QColor('gray'))

    def testReduceRGB(self):
        self.reduceColor(QColor.fromRgbF(0.1, 0.2, 0.3, 0.4))

    def testReduceCMYK(self):
        self.reduceColor(QColor.fromCmykF(0.1, 0.2, 0.3, 0.4, 0.5))

    def testReduceHsl(self):
        self.reduceColor(QColor.fromHslF(0.1, 0.2, 0.3, 0.4))

    def testReduceHsv(self):
        self.reduceColor(QColor.fromHsvF(0.1, 0.2, 0.3, 0.4))

if __name__ == "__main__":
    unittest.main()

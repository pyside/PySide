#!/usr/bin/python
'''Test cases for QLineF'''

import unittest
import os

from PySide.QtCore import *

class TestQLineF (unittest.TestCase):
    def testIntersect(self):
        l1 = QLineF(0, 0, 1, 0)
        l2 = QLineF(1, -1, 1, 1)
        tuple_ = l1.intersect(l2)
        self.assertEquals(tuple, tuple_.__class__)
        (value, p) = tuple_
        self.assertEquals(QLineF.BoundedIntersection, value)
        self.assertEqual(QPointF(1, 0), p)

if __name__ == '__main__':
    unittest.main()

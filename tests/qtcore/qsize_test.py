#!/usr/bin/python
'''Unit tests for QSize'''

import unittest

from PySide.QtCore import QSize

class QSizeOperator(unittest.TestCase):
    def testOperatorMultiply(self):
        #QSize operator * float
        # bug 131
        a = QSize(1, 1)
        x = a * 3.4
        self.assertEqual(QSize(3, 3), x)

    def testOperatorRevertedMultiply(self):
        #QSize operator * float, reverted
        # bug 132
        a = QSize(1, 1)
        x = 3.4 * a
        self.assertEqual(QSize(3, 3), x)


if __name__ == '__main__':
    unittest.main()


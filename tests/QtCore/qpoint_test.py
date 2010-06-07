
'''Test cases for QPoint and QPointF'''

import unittest

from PySide.QtCore import QPoint, QPointF


class QPointTest(unittest.TestCase):

    def testQPointCtor(self):
        point = QPoint(QPoint(10,20))

class QPointFTest(unittest.TestCase):

    def testQPointFCtor(self):
        pointf = QPointF(QPoint(10,20))

if __name__ == '__main__':
    unittest.main()


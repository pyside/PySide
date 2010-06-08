#!/usr/bin/python
'''Tests the presence of unary operator __neg__ on the QPoint class'''

import unittest

from PySide.QtCore import QPoint

class NegUnaryOperatorTest(unittest.TestCase):
    '''Tests the presence of unary operator __neg__ on the QPoint class'''

    def setUp(self):
        #Acquire resources
        self.x, self.y = 10, 20
        self.neg_x, self.neg_y = -self.x, -self.y
        self.qpoint = QPoint(self.x, self.y)

    def tearDown(self):
        #Release resources
        del self.qpoint
        del self.x
        del self.y
        del self.neg_x
        del self.neg_y

    def testNegUnaryOperator(self):
        #Test __neg__ unary operator on QPoint class
        __neg__method_exists = True
        try:
            neg_qpoint = -self.qpoint
        except:
            __neg__method_exists = False

        self.assertTrue(__neg__method_exists)
        self.assertEqual(self.qpoint, -neg_qpoint)

if __name__ == '__main__':
    unittest.main()


import gc
import unittest

from PySide.QtCore import qsrand

class OverflowExceptionCollect(unittest.TestCase):
    '''Test case for OverflowError exception during garbage collection. See bug #147'''

    def testOverflow(self):
        # NOTE: PyQt4 raises TypeError, but boost.python raises OverflowError
        self.assertRaises(OverflowError, qsrand, 42415335332353253)
        # should not abort if bug #147 is fixed
        gc.collect()

if __name__ == '__main__':
        unittest.main()

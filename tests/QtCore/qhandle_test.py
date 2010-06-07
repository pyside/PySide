#!/usr/bin/python
'''Test cases for QEnum and QFlags'''

import unittest

from PySide.QtCore import QThread, Qt

class TestHANDLE(unittest.TestCase):
    def testIntConversion(self):
        i = 0
        h = QThread.currentThreadId()
        i = 0 + int(h)
        self.assertEqual(i, int(h))

if __name__ == '__main__':
    unittest.main()

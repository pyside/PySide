'''Test cases for QIPv6Address'''

import unittest

from PySide.QtNetwork import *

class QIPv6AddressGetItemTest(unittest.TestCase):
    def testLength(self):
        ip = QIPv6Address()
        self.assertEqual(len(ip), 16)

    def testSetItemNegativeIndex(self):
        ip = QIPv6Address()
        ip[-1] = 8
        self.assertEqual(ip[-1], 8)

    def testSetItemLargeIndex(self):
        ip = QIPv6Address()
        self.assertRaises(IndexError, ip.__setitem__, 32, 16)

if __name__ == '__main__':
    unittest.main()

#!/usr/bin/python
'''Test cases for QEnum and QFlags'''

import unittest

from PySide.QtCore import *

class TestEnum(unittest.TestCase):

    def testToInt(self):
        self.assertEqual(QIODevice.NotOpen, 0)
        self.assertEqual(QIODevice.ReadOnly, 1)
        self.assertEqual(QIODevice.WriteOnly, 2)
        self.assertEqual(QIODevice.ReadWrite, 1 | 2)
        self.assertEqual(QIODevice.Append, 4)
        self.assertEqual(QIODevice.Truncate, 8)
        self.assertEqual(QIODevice.Text, 16)
        self.assertEqual(QIODevice.Unbuffered, 32)

    def testToIntInFunction(self):
        self.assertEqual(str(int(QIODevice.WriteOnly)), "2")

class TestQFlags(unittest.TestCase):
    def testToItn(self):
        om = QIODevice.NotOpen

        self.assertEqual(om, QIODevice.NotOpen)
        self.assertTrue(om == 0)

        self.assertTrue(om != QIODevice.ReadOnly)
        self.assertTrue(om != 1)

    def testToIntInFunction(self):
        om = QIODevice.WriteOnly
        self.assertEqual(int(om), 2)

    def testNonExtensibleEnums(self):
        try:
            om = QIODevice.OpenMode(QIODevice.WriteOnly)
            self.assertFail()
        except:
            pass

if __name__ == '__main__':
    unittest.main()

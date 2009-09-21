#!/usr/bin/python
'''Test cases for QEnum and QFlags'''

import unittest

from PySide.QtCore import QIODevice, QString, Qt, QVariant

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
        self.assertEqual(QString.number(QIODevice.WriteOnly), "2")

class TestQFlags(unittest.TestCase):
    def testToItn(self):
        om = QIODevice.OpenMode(QIODevice.NotOpen)

        self.assertEqual(om, QIODevice.NotOpen)
        self.assertTrue(om == 0)

        self.assertTrue(om != QIODevice.ReadOnly)
        self.assertTrue(om != 1)

    def testToIntInFunction(self):
        om = QIODevice.OpenMode(QIODevice.WriteOnly)
        self.assertEqual(QString.number(int(om)), "2")

class TestDuplicatedValues(unittest.TestCase):
    def testQVariant(self):
        self.assertEqual(QVariant.LastCoreType, QVariant.Hash)
        self.assertEqual(QVariant.LastGuiType, QVariant.Transform)

if __name__ == '__main__':
    unittest.main()

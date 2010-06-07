#!/usr/bin/python
'''Unit tests for QLocale'''

import unittest
import ctypes
import sys

from PySide.QtCore import QLocale

class QLocaleTestToNumber(unittest.TestCase):
    def testToNumberInt(self):
        obj = QLocale(QLocale.C)
        self.assertEqual((37, True), obj.toInt('37'))

    def testToNumberFloat(self):
        obj = QLocale(QLocale.C)
        self.assertEqual((ctypes.c_float(37.109).value, True),
                         obj.toFloat('37.109'))

    def testToNumberDouble(self):
        obj = QLocale(QLocale.C)
        self.assertEqual((ctypes.c_double(37.109).value, True),
                         obj.toDouble('37.109'))

    def testToNumberShort(self):
        obj = QLocale(QLocale.C)
        self.assertEqual((ctypes.c_short(37).value, True),
                         obj.toShort('37'))

    def testToNumberULongLong(self):
        obj = QLocale(QLocale.C)
        self.assertEqual((ctypes.c_ulonglong(37).value, True),
                         obj.toULongLong('37'))

    def testToNumberULongLongNegative(self):
        obj = QLocale(QLocale.C)
        self.assert_(not obj.toULongLong('-37')[1])

if __name__ == '__main__':
    unittest.main()

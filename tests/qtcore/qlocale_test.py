#!/usr/bin/python
'''Unit tests for QLocale'''

import unittest
import ctypes
import sys

from PySide.QtCore import QLocale

class QLocaleTestToNumber(unittest.TestCase):
    def testToNumberInt(self):
        obj = QLocale(QLocale.C)
        self.assertEqual(37, obj.toInt('37')[0])

    def testToNumberFloat(self):
        obj = QLocale(QLocale.C)
        self.assertEqual(ctypes.c_float(37.109).value,
                         obj.toFloat('37.109')[0])

    def testToNumberDouble(self):
        obj = QLocale(QLocale.C)
        self.assertEqual(ctypes.c_double(37.109).value,
                         obj.toDouble('37.109')[0])

if __name__ == '__main__':
    unittest.main()

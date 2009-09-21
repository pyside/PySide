#!/usr/bin/python
'''Unit tests for QByteArray'''

import unittest
import ctypes
import sys

from PySide.QtCore import QByteArray

class QByteArrayTestToNumber(unittest.TestCase):
    def testToNumberInt(self):
        obj = QByteArray('37')
        self.assertEqual(37, obj.toInt()[0])

    def testToNumberFloat(self):
        obj = QByteArray('37.109')
        self.assertEqual(ctypes.c_float(37.109).value,
                         obj.toFloat()[0])

    def testToNumberDouble(self):
        obj = QByteArray('37.109')
        self.assertEqual(ctypes.c_double(37.109).value,
                         obj.toDouble()[0])

class QByteArraySplit(unittest.TestCase):
    '''Test case for QByteArray.split'''

    def testPathSeparator(self):
        #QByteArray.split('/')
        obj = QByteArray(unittest.__file__)
        self.assertEqual(obj.split('/'), unittest.__file__.split('/'))

class QByteArrayData(unittest.TestCase):

    '''Test case for QByteArray.data'''

    def testData(self):
        url = QByteArray("http://web.openbossa.org/")
        self.assertEqual(url.data(), "http://web.openbossa.org/")


if __name__ == '__main__':
    unittest.main()

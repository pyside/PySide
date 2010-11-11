#!/usr/bin/python
'''Unit tests for QByteArray'''

import unittest
import ctypes
import sys

from PySide.QtCore import *

class QByteArrayTestToNumber(unittest.TestCase):
    def testToNumberInt(self):
        obj = QByteArray('37')
        self.assertEqual((37, True), obj.toInt())

    def testToNumberUShort(self):
        obj = QByteArray('37')
        self.assertEqual((37, True), obj.toUShort())

    def testToNumberFloat(self):
        obj = QByteArray('37.109')
        self.assertEqual((ctypes.c_float(37.109).value, True),
                         obj.toFloat())

    def testToNumberDouble(self):
        obj = QByteArray('37.109')
        self.assertEqual((ctypes.c_double(37.109).value, True),
                         obj.toDouble())

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

    def testDataWithZeros(self):
        s1 = "123\000321"
        ba = QByteArray(s1)
        s2 = ba.data()
        self.assertEqual(s1, s2)

class QByteArrayOperatorAtSetter(unittest.TestCase):
    '''Test case for operator QByteArray[] - __setitem__'''

    def testSetterString(self):
        '''QByteArray[x] = pythonstring'''
        obj = QByteArray('123456')
        obj[1] = '0'
        self.assertEqual(obj, QByteArray('103456'))

    def testSetterStringLarge(self):
        '''QByteArray[x] = pythonstring (larget than 1 char)'''
        obj = QByteArray('123456')
        obj[3] = 'abba'
        self.assertEqual(obj, QByteArray('123abba56'))

    def testSetterQByteArray(self):
        '''QByteArray[x] = qbytearray'''
        obj = QByteArray('123456')
        obj[3] = QByteArray('array')
        self.assertEqual(obj, QByteArray('123array56'))


class QByteArrayOperatorAtSetterNegativeIndex(unittest.TestCase):
    '''Test case for QByteArray[] - __setitem__ - for negative index'''

    def testSetterNegativeIndex(self):
        '''QByteArray[x] = string - negative index'''
        obj = QByteArray('123456')
        obj[-3] = 'array'
        self.assertEqual(obj, QByteArray('123array56'))


class QByteArrayOperatorAtSetterLargeIndex(unittest.TestCase):
    '''Test case for QByteArray[] - __setitem__ - for 'overflown' index'''

    def testSetterLargeIndexEmpty(self):
        '''QByteArray[x] = somestring - Overflow index on empty string'''
        # should pad with spaces if the index is larger
        obj = QByteArray('')
        obj[2] = 'a'
        self.assertEqual(obj, QByteArray('  a'))

    def testSetterLargeIndexNormal(self):
        '''QByteArray[x] = somestring - Overflow index on normal string'''
        # should pad with spaces if the index is larger
        obj = QByteArray('mystring')
        obj[10] = 'normal'
        self.assertEqual(obj, QByteArray('mystring  normal'))

class QByteArrayOnQVariant(unittest.TestCase):
    def testQByteArrayOnQVariant(self):
        a = QSettings().value("some_prop", QByteArray())
        self.assertEqual(type(a), QByteArray)

if __name__ == '__main__':
    unittest.main()

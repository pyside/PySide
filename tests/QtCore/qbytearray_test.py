#!/usr/bin/python
'''Unit tests for QByteArray'''

import unittest
import ctypes
import sys
import pickle
import cStringIO

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

    def testSetNum(self):
        b = QByteArray()
        b.setNum(-124124L)
        self.assertEqual(b, "-124124")
        b = QByteArray()
        b.setNum(-124124)
        self.assertEqual(b, "-124124")
        b = QByteArray()
        b.setNum(-0.5)
        self.assertEqual(b, "-0.5")

    def testAppend(self):
        b = QByteArray()
        b.append("A")
        self.assertEqual(b.size(), 1)
        b.append("AB")
        self.assertEqual(b.size(), 3)


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
        self.assertEqual(s1, ba)

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

class TestBug666(unittest.TestCase):
    '''QByteArray does not support slices'''
    def testIt(self):
        ba = QByteArray('1234567890')
        self.assertEqual(ba[2:4], '34')
        self.assertEqual(ba[:4], '1234')
        self.assertEqual(ba[4:], '567890')
        self.assertEqual(len(ba[4:1]), 0)

class QByteArrayBug514(unittest.TestCase):
    def testIt(self):
        data = "foobar"
        a = QByteArray.fromRawData(data)
        self.assertEqual(type(a), QByteArray)
        self.assertEqual(a.data(), data)

class TestPickler(unittest.TestCase):
    def testIt(self):
        ba = QByteArray("321\x00123")
        output = cStringIO.StringIO()
        pickle.dump(ba, output)
        ba2 = pickle.loads(output.getvalue())
        self.assertEqual(ba, ba2)


if __name__ == '__main__':
    unittest.main()

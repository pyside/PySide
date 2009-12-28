#!/usr/bin/python
# -*- coding: utf-8 -*-
'''Test cases for QString'''

import unittest
import ctypes
import sys

from PySide.QtCore import QString, QByteArray

class QStringToNumber(unittest.TestCase):
    def testReturnValueTypes(self):
        obj = QString('37')
        val, ok = obj.toInt()
        self.assertEqual(type(val), int)
        self.assertEqual(type(ok), bool)

    def testToNumberInt(self):
        obj = QString('37')
        self.assertEqual(37, obj.toInt()[0])

    def testToNumberIntUsingHex(self):
        obj = QString('2A')
        self.assertEquals((0, False), obj.toInt())
        self.assertEqual((int(str(obj), 16), True), obj.toInt(16))

    def testToNumberIntUsingHex(self):
        obj = QString('101010')
        self.assertEqual((int(str(obj), 2), True), obj.toInt(2))

    def testToNumberFloat(self):
        obj = QString('37.109')
        self.assertEqual(ctypes.c_float(37.109).value,
                         obj.toFloat()[0])

    def testToNumberDouble(self):
        obj = QString('37.109')
        self.assertEqual(ctypes.c_double(37.109).value,
                         obj.toDouble()[0])

    def testToULongLong(self):
        obj = QString('37109')
        self.assertEqual(ctypes.c_ulong(37109).value,
                        obj.toULongLong()[0])

class QStringConstructor(unittest.TestCase):
    '''Test case for QString constructors'''

    def testQStringDefault(self):
        #QString()
        obj1 = QString()
        obj2 = QString()

        self.assertEqual(obj1, obj2)

    def testQStringFromPy(self):
        #QString(const char*)
        sample = 'a new string'
        obj1 = QString(sample)
        obj2 = QString(sample)
        self.assertEqual(obj1, obj2)

    def testQStringFromUnicode(self):
        sample = u'áâãà'
        obj1 = QString(sample)
        obj2 = QString(sample)
        self.assertEqual(obj1, obj2)
        self.assertEqual(obj1, sample)
        self.assertEqual(obj2, sample)

    def testQStringFromByteArray(self):
        # QByteArray(const char *) must be working
        sample = QByteArray('foo')
        obj1 = QString(sample)
        obj2 = QString(sample)
        self.assertEqual(obj1, obj2)

    def testQStringArg(self):
        a = QString("%1 %2 %3").arg(1).arg("two").arg(3.14)
        self.assertEquals("1 two 3.14", str(a))

    def testQStringArgNegative(self):
        a = QString("%1").arg(-20)
        self.assertEquals("-20", str(a))


class QStringComparison(unittest.TestCase):
    '''Test case for comparison to python strings'''

    def testComparePyString(self):
        #Compare QStrings and Python strings.
        py = ''
        qstr = QString()
        self.assertEqual(py, qstr)

        py = 'The quick brown fox jumps over the lazy dog'
        qstr = QString(py)
        self.assertEqual(py, qstr)

class QStringRange(unittest.TestCase):
    '''Test case for ranges in python strings'''

    def testSimpleRange(self):
        #Test open start and open end intervals
        py = 'The quick brown fox jumps over the lazy dog'
        qstr = QString(py)
        self.assertEqual(py[5:], qstr[5:])
        self.assertEqual(py[:7], qstr[:7])

class QStringIndexOf(unittest.TestCase):
    def testEmpty(self):
        string = QString()
        self.assertEqual(string.indexOf(QString("aaa")), -1)
        self.assertEqual(string.indexOf(QString()), 0)

    def testString(self):
        string = QString("the quick brown fox")
        self.assertEqual(string.indexOf("quick", 0), 4)

if __name__ == '__main__':
    unittest.main()

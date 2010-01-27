#!/usr/bin/python
# -*- coding: utf-8 -*-
'''Test cases for QString operators'''

import unittest

from PySide.QtCore import QString, QByteArray

class QStringOperatorEqual(unittest.TestCase):
    '''TestCase for operator QString == QString'''

    def testDefault(self):
        #QString() == QString()
        obj1 = QString()
        obj2 = QString()
        self.assertEqual(obj1, obj2)

    def testSimple(self):
        #QString(some_string) == QString(some_string)
        string = 'egg snakes'
        self.assertEqual(QString(string), QString(string))

    def testUnicode(self):
        #QString(unicode) == QString(unicode)
        string = u'àâãá'
        self.assertEqual(QString(string), QString(string))

    def testPyString(self):
        #QString(string) == string
        string = 'my test string'
        self.assertEqual(QString(string), string)
        self.assertEqual(string, QString(string))

    def testPyUnicodeString(self):
        #QString(unicode) == unicode
        string = u'àâãá'
        self.assertEqual(QString(string), string)
        self.assertEqual(string, unicode(QString(string)))

    def testQByteArray(self):
        #QString(string) == QByteArray(string)
        string = 'another test string'
        self.assertEqual(QString(string), QByteArray(string))


class QStringOperatorAtSetter(unittest.TestCase):
    '''Test case for operator QString[] - __setitem__'''

    def testSetterString(self):
        '''QString[x] = pythonstring'''
        obj = QString('123456')
        obj[1] = '0'
        self.assertEqual(obj, QString('103456'))

    def testSetterStringLarge(self):
        '''QString[x] = pythonstring (larget than 1 char)'''
        obj = QString('123456')
        obj[3] = 'abba'
        self.assertEqual(obj, QString('123abba56'))

    def testSetterQString(self):
        '''QString[x] = QString'''
        obj = QString('123456')
        obj[3] = QString('string')
        self.assertEqual(obj, QString('123string56'))

    def testSetterQByteArray(self):
        '''QString[x] = qbytearray'''
        obj = QString('123456')
        obj[3] = QByteArray('array')
        self.assertEqual(obj, QString('123array56'))


class QStringOperatorAtSetterNegativeIndex(unittest.TestCase):
    '''Test case for QString[] - __setitem__ - for negative index'''

    def testSetterNegativeIndex(self):
        '''QString[x] = string - negative index'''
        obj = QString('123456')
        obj[-3] = 'array'
        self.assertEqual(obj, QString('123array56'))


class QStringOperatorAtSetterLargeIndex(unittest.TestCase):
    '''Test case for QString[] - __setitem__ - for 'overflown' index'''

    def testSetterLargeIndexEmpty(self):
        '''QString[x] = somestring - Overflow index on empty string'''
        # should pad with spaces if the index is larger
        obj = QString('')
        obj[2] = 'a'
        self.assertEqual(obj, QString('  a'))

    def testSetterLargeIndexNormal(self):
        '''QString[x] = somestring - Overflow index on normal string'''
        # should pad with spaces if the index is larger
        obj = QString('mystring')
        obj[10] = 'normal'
        self.assertEqual(obj, QString('mystring  normal'))


class QStringOperatorAt(unittest.TestCase):
    '''TestCase for operator QString[] - __getitem__'''

    def testInRange(self):
        #QString[x] where x is a valid index
        string = 'abcdefgh'
        obj = QString(string)

        for i in range(len(string)):
            self.assertEqual(obj[i], string[i])

    def testInRangeReverse(self):
        #QString[x] where x is a valid index (reverse order)
        string = 'abcdefgh'
        obj = QString(string)

        for i in range(len(string)-1, 0, -1):
            self.assertEqual(obj[i], string[i])


    def testInRangeUnicode(self):
        #QString[x] where x is a valid index (unicode)
        string = u'àâãá'
        obj = QString(string)

        for i in range(len(string)):
            self.assertEqual(obj[i], string[i])

    def testInRangeUnicodeReverse(self):
        #QString[x] where x is a valid index (unicode) (reverse order)
        string = u'àâãá'
        obj = QString(string)

        for i in range(len(string)-1, 0, -1):
            self.assertEqual(obj[i], string[i])

    def testOutOfRange(self):
        #QString[x] where x is out of index
        string = '1234567'
        obj = QString(string)
        self.assertRaises(IndexError, lambda :obj[len(string)])

    def testReturnQString(self):
        #QString[x] must return a QString
        string = QString('123456')
        data = string[0]
        self.assert_(isinstance(data, QString))

class QStringOperatorAdd(unittest.TestCase):
    '''TestCase for operator QString[]'''

    def testOperatorAdd(self):
        str1 = '123'
        str2 = QString('456')
        self.assertEquals('123456', str1 + str2)
        self.assertEquals('456123', str2 + str1)


if __name__ == '__main__':
    unittest.main()

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

class QStringOperatorAt(unittest.TestCase):
    '''TestCase for operator QString[]'''

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

#!/usr/bin/python
# -*- coding: utf-8 -*-
'''Test cases for QByteArray operators'''

import unittest

from PySide.QtCore import QByteArray, QString

class QByteArrayOperatorEqual(unittest.TestCase):
    '''TestCase for operator QByteArray == QByteArray'''

    def testDefault(self):
        #QByteArray() == QByteArray()
        obj1 = QByteArray()
        obj2 = QByteArray()
        self.assertEqual(obj1, obj2)

    def testSimple(self):
        #QByteArray(some_string) == QByteArray(some_string)
        string = 'egg snakes'
        self.assertEqual(QByteArray(string), QByteArray(string))

    def testPyString(self):
        #QByteArray(string) == string
        string = 'my test string'
        self.assertEqual(QByteArray(string), string)

    def testQString(self):
        #QByteArray(string) == QString(string)
        string = 'another test string'
        self.assertEqual(QByteArray(string), QString(string))

class QByteArrayOperatorAt(unittest.TestCase):
    '''TestCase for operator QByteArray[]'''

    def testInRange(self):
        #QByteArray[x] where x is a valid index
        string = 'abcdefgh'
        obj = QByteArray(string)

        for i in range(len(string)):
            self.assertEqual(obj[i], string[i])

    def testInRangeReverse(self):
        #QByteArray[x] where x is a valid index (reverse order)
        string = 'abcdefgh'
        obj = QByteArray(string)

        for i in range(len(string)-1, 0, -1):
            self.assertEqual(obj[i], string[i])


    def testOutOfRange(self):
        #QByteArray[x] where x is out of index
        string = '1234567'
        obj = QByteArray(string)
        self.assertRaises(IndexError, lambda :obj[len(string)])


if __name__ == '__main__':
    unittest.main()

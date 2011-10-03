#!/usr/bin/python
# -*- coding: utf-8 -*-
'''Test cases for QByteArray operators'''

import unittest
import py3kcompat as py3k

from PySide.QtCore import QByteArray

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
        #QByteArray(string) == string
        string = 'another test string'
        self.assertEqual(QByteArray(string), string)

class QByteArrayOperatorAt(unittest.TestCase):
    '''TestCase for operator QByteArray[]'''

    def testInRange(self):
        #QByteArray[x] where x is a valid index
        string = 'abcdefgh'
        obj = QByteArray(string)

        for i in range(len(string)):
            self.assertEqual(obj[i], py3k.b(string[i]))

    def testInRangeReverse(self):
        #QByteArray[x] where x is a valid index (reverse order)
        string = 'abcdefgh'
        obj = QByteArray(string)

        for i in range(len(string)-1, 0, -1):
            self.assertEqual(obj[i], py3k.b(string[i]))


    def testOutOfRange(self):
        #QByteArray[x] where x is out of index
        string = '1234567'
        obj = QByteArray(string)
        self.assertRaises(IndexError, lambda :obj[len(string)])

    def testNullStrings(self):
        ba = QByteArray('\x00')
        self.assertEqual(ba.at(0), '\x00')
        self.assertEqual(ba[0], py3k.b('\x00'))

class QByteArrayOperatorLen(unittest.TestCase):
    '''Test case for __len__ operator of QByteArray'''

    def testBasic(self):
        '''QByteArray __len__'''
        self.assertEqual(len(QByteArray()), 0)
        self.assertEqual(len(QByteArray('')), 0)
        self.assertEqual(len(QByteArray(' ')), 1)
        self.assertEqual(len(QByteArray('yabadaba')), 8)


class QByteArrayOperatorStr(unittest.TestCase):
    '''Test case for __str__ operator of QByteArray'''

    def testBasic(self):
        '''QByteArray __str__'''
        self.assertEqual(QByteArray().__str__(), '')
        self.assertEqual(QByteArray('').__str__(), '')
        self.assertEqual(QByteArray('aaa').__str__(), 'aaa')


if __name__ == '__main__':
    unittest.main()

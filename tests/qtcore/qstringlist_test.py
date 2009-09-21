
# -*- coding: utf-8 -*-

'''Test cases for QStringList'''

import unittest
from random import shuffle

from PySide.QtCore import QStringList, QString

from helper import random_string

class UsesManyStrings(unittest.TestCase):
    '''Helper class to setup a list of strings and QStrings'''
    def setUp(self):
        #Creates a list of strings and python strings
        self.size = 10
        # List of Python strings
        self.samples = [random_string() for x in range(self.size)]
        # List of QStrings
        self.strings = map(QString, self.samples)

        self.obj = QStringList(self.strings)


class TestConstructorBasic(unittest.TestCase):
    '''Basic constructor test'''

    def testEmpty(self):
        #QStringList() - default constructor
        obj = QStringList()
        self.assert_(isinstance(obj, QStringList))

    def testQString(self):
        #QStringList(QString)
        qstr = QString('aaaa')
        obj = QStringList(qstr)
        self.assert_(isinstance(obj, QStringList))

    def testPyString(self):
        #QStringList(python_string) constructor
        string = 'forty two'
        obj = QStringList(string)
        self.assert_(isinstance(obj, QStringList))

    def testPyStringUnicode(self):
        #QStringList(unicode python_string) constructor
        string = 'Nação Zumbi'
        obj = QStringList(string)
        self.assert_(isinstance(obj, QStringList))


class TestConstructorList(UsesManyStrings):
    '''Test case for QStringList(List) constructor'''

    def testListQString(self):
        #QStringList([QString]) constructor
        obj = QStringList(self.strings)
        self.assert_(isinstance(obj, QStringList))

    def testListPyString(self):
        #QStringList([python_string]) constructor
        obj = QStringList(self.samples)
        self.assert_(isinstance(obj, QStringList))

    def testListMixed(self):
        #QStringList([python_string and QString]) mixed constructor
        mixed = self.samples + self.strings
        shuffle(mixed)
        obj = QStringList(mixed)
        self.assert_(isinstance(obj, QStringList))

    def testCopyList(self):
        #QStringList(QStringList(list)) - copy constructor
        obj = QStringList(self.strings)
        obj2 = QStringList(obj)
        self.assert_(isinstance(obj2, QStringList))
        self.assertEqual(obj, obj2)


class TestComparison(unittest.TestCase):
    '''Test case for comparison of QStringLists'''

    def testEqual(self):
        #QStringList == QStringList
        string = QString('aaaabvbbcccedde')
        obj1 = QStringList(string)
        obj2 = QStringList(string)
        self.assertEqual(obj1, obj2)


class TestIndexing(unittest.TestCase):
    '''Test case for indexing through []'''
    def testInvalidIndexEmpty(self):
        #QStringList[x] for empty list
        obj = QStringList()
        self.assertRaises(IndexError, lambda:obj[0])

    def testInvalidIndexQString(self):
        #QStringList[1] raising IndexError for QStringList(QString)
        obj = QStringList(QString('aaaaa'))
        self.assertRaises(IndexError, lambda:obj[1])

    def testValidIndexQString(self):
        #QStringList[0] not raising IndexError for QStringList(QString)
        string = QString('abcdefg')
        obj = QStringList(string)
        self.assertEqual(obj[0], string)

    def testNegativeIndexing(self):
        #QStringList[-1] not raising IndexError for QStringList(QString)
        string = QString('abcdefg')
        obj = QStringList(string)
        self.assertEqual(obj[-1], string)


class TestListIndexing(UsesManyStrings):
    '''Test case for indexing QStringList longer than 1 string'''

    def testValid(self):
        #QStringList[] for valid indexes
        for i in range(self.size):
            self.assertEqual(self.strings[i], self.obj[i])

    def testNegativeValid(self):
        #QStringList[] for valid indexes
        for i in range(-1, -self.size, -1):
            self.assertEqual(self.strings[i], self.obj[i])

    def testInvalid(self):
        #QStringList[] for invalid negative indexes
        self.assertRaises(IndexError, lambda : self.obj[self.size])
        self.assertRaises(IndexError, lambda : self.obj[-(self.size+1)])


class TestSlicing(UsesManyStrings):
    '''Test case for slicing a QStringList'''

    def testSlicing(self):
        #QStringList slicing
        for i in range(self.size):
            self.assertEqual(self.obj[i:], self.strings[i:])
            self.assertEqual(self.obj[:i], self.strings[:i])
            for j in range(i):
                self.assertEqual(self.obj[j:i], self.strings[j:i])

        for i in range(-1, -self.size, -1):
            self.assertEqual(self.obj[:i], self.strings[:i])


class TestShiftOperator(UsesManyStrings):
    '''Test case for QStringList lshift operator'''

    def testShiftOperator(self):
        #QStringList lshift
        a = QStringList()
        a << "a" << "b" << "c";
        self.assertEquals(3, a.count())
        b = ["1", "2", "3"]
        c = ["4", "5", "6"]
        a << b << c
        self.assertEquals(9, a.count())

if __name__ == '__main__':
    unittest.main()

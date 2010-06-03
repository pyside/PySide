#!/usr/bin/python
# -*- coding: utf-8 -*-
'''Test cases for QVariant'''

import unittest
import sys

from PySide.QtCore import *


class QVariantToNumber(unittest.TestCase):
    '''QVariant of number types'''

    def testToNumberInt(self):
        '''QVariant(int).toInt()'''
        obj = QVariant('37')
        self.assertEqual((37, True), obj.toInt())

    def testToNumberLongLong(self):
        '''QVariant(int).toLongLong()'''
        obj = QVariant('37')
        self.assertEqual((37, True), obj.toLongLong())

    def testToNumberUInt(self):
        '''QVariant(int).toUInt()'''
        obj = QVariant('37')
        self.assertEqual((37, True), obj.toUInt())

    def testToNumberUIntNegative(self):
        '''QVariant(negative int).toUInt()'''
        obj = QVariant('-37')
        self.assert_(not obj.toUInt()[1])

    def testToNumberULongLong(self):
        '''QVariant(int).toULongLong()'''
        obj = QVariant('37')
        self.assertEqual((37, True), obj.toULongLong())

    def testToNumberULongLongNegative(self):
        '''QVariant(negative int).toULongLong()'''
        obj = QVariant('-37')
        self.assert_(not obj.toULongLong()[1])

    def testToNumberFloat(self):
        '''QVariant(double).toFloat()'''
        obj = QVariant('37.109')
        self.assertEqual((37.109, True), obj.toDouble())


class QVariantTypeName(unittest.TestCase):
    '''QVariant.typeName()'''

    def testTypeNameString(self):
        '''QVariant(PyString).typeName()'''
        obj = QVariant('aaaa')
        self.assertEqual('QString', obj.typeName())

    def testTypeNameInt(self):
        '''QVariant(int).typeName()'''
        obj = QVariant(34)
        self.assertEqual('int', obj.typeName())

    def testTypeNameDouble(self):
        '''QVariant(double).typeName()'''
        obj = QVariant(3.14)
        self.assertEqual('double', obj.typeName())

    def testTypeNameBool(self):
        '''QVariant(bool).typeName()'''
        obj = QVariant(True)
        self.assertEqual('bool', obj.typeName())

    def testTypeNameQByteArray(self):
        '''QVariant(QByteArray).typeName()'''
        obj = QVariant(QByteArray('aaaa'))
        self.assertEqual('QByteArray', obj.typeName())

    def testTypeNameNone(self):
        '''QVariant().typeName()'''
        obj = QVariant()
        self.assertEqual(None, obj.typeName())

    def testTypeNameQVariantList(self):
        '''QVariant(QVariantList).typeName()'''
        obj = QVariant([1, 2, 3, 4])
        self.assertEqual('QVariantList', obj.typeName())

        obj = QVariant([1.0, 2.2, 3.3, 4.2])
        self.assertEqual('QVariantList', obj.typeName())

        obj = QVariant(['aaa', 'bbb', 'ccc', 'dddd'])
        self.assertEqual('QVariantList', obj.typeName())

class QVariantConstructor(unittest.TestCase):
    '''More qvariant constructions'''

    def testCopyConstructor(self):
        '''QVariant copy constructor'''
        obj = QVariant(1)
        cpy = QVariant(obj)

        self.assertEqual(obj.type(), cpy.type())

    def testQStringConstructor(self):
        '''QVariant(PyString).type == QVariant.string'''
        obj = QVariant("PySide")
        self.assertEqual(obj.type(), QVariant.String)

    def testQSizeConstructor(self):
        '''QVariant(QSize).type == QVariant.Size'''
        mysize = QSize(0, 0)
        variant = QVariant(mysize)

        self.assertEqual(variant.type(), QVariant.Size)
        self.assertEqual(variant.toSize(), mysize)

    def testToList(self):
        v = QVariant((1,2,3))
        self.assertEqual(v.toList(), (1, 2, 3))
        v = QVariant([0,1,2])
        self.assertEqual(v.toList(), [0, 1, 2])

if __name__ == '__main__':
    unittest.main()

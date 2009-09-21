#!/usr/bin/python
# -*- coding: utf-8 -*-
'''Test cases for QVariant'''

import unittest
import sys

from PySide.QtCore import QSize, QVariant, QByteArray, QStringList

class Dummy(object):
    pass

class MySize(QSize):
    pass

class QVariantToNumber(unittest.TestCase):
    def testToNumberInt(self):
        obj = QVariant('37')
        self.assertEqual(37, obj.toInt()[0])

    def testToNumberFloat(self):
        obj = QVariant('37.109')
        self.assertEqual(37.109, obj.toDouble()[0])

class QVariantTypeName(unittest.TestCase):
    def testTypeNameQString(self):
        #QVariant.typeName()
        obj = QVariant('aaaa')
        self.assertEqual('QString', obj.typeName())

    def testTypeNameInt(self):
        obj = QVariant(34)
        self.assertEqual('int', obj.typeName())

    def testTypeNameDouble(self):
        obj = QVariant(3.14)
        self.assertEqual('double', obj.typeName())

    def testTypeNameBool(self):
        obj = QVariant(True)
        self.assertEqual('bool', obj.typeName())

    def testTypeNameQByteArray(self):
        obj = QVariant(QByteArray('aaaa'))
        self.assertEqual('QByteArray', obj.typeName())

    def testTypeNameNone(self):
        obj = QVariant()
        self.assertEqual(None, obj.typeName())

    def testTypeNameQVariantList(self):
        obj = QVariant([1,Dummy(),3,4])
        self.assertEqual('QVariantList', obj.typeName())

    def testTypeNameQStringList(self):
        obj = QVariant(QStringList())
        self.assertEqual('QStringList', obj.typeName())

    def testTypeNamePythonClasses(self):
        ## QVariant of python classes
        d = Dummy()
        obj = QVariant(d)
        self.assertEqual('PyQt_PyObject', obj.typeName())

    # This works only on PyQt4 4.5.x, not on PyQt4 4.4.x or PySide
    def testSubClassConvertion(self):
        mysize = MySize(0, 0)
        variant = QVariant(mysize)

        assert(variant.type() != QVariant.Size)
        assert(variant.toPyObject() is mysize)

class QVariantConstructor(unittest.TestCase):
    def testCopyConstructor(self):
        obj = QVariant(1)
        cpy = QVariant(obj)

        self.assertEqual(obj.type(), cpy.type())

    def testQStringConstructor(self):
        obj = QVariant("PySide")
        self.assertEqual(obj.type(), QVariant.String)

class QVariantToPyObject(unittest.TestCase):
    def testQVariantPyList(self):
        obj = QVariant([1, 'two', 3])
        self.assertEqual(obj.toPyObject(), [1, 'two', 3])

    def testPyObject(self):
        d = Dummy()
        obj = QVariant(d)
        self.assertEqual(d, obj.toPyObject())

    def atestNoneToPyObject(self):
        # XXX Do not run by default because segfaults with PyQt4
        obj = QVariant()
        self.assertEqual(None, obj.toPyObject())

    def testQStringToPyObject(self):
        d = 'abc'
        obj = QVariant('abc')
        self.assertEqual(d, obj.toPyObject())

class QVartiantTypeTest(unittest.TestCase):
    def testQSize(self):
        class MySize(QSize):
            pass

        mysize = MySize(5, 5)
        variant = QVariant(mysize)
        self.assert_(variant.type() != QVariant.Size)
        self.assert_(variant.toPyObject() is mysize)

if __name__ == '__main__':
    unittest.main()

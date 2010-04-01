#!/usr/bin/python
# -*- coding: utf-8 -*-
'''Test cases for QVariant with QtGui types'''

import unittest

from PySide.QtCore import *
from PySide.QtGui import *

from helper import UsesQApplication

class Dummy(object):
    pass

class QVariantTypeName(unittest.TestCase):
    def testQPen(self):
        obj = QVariant(QPen(Qt.red))
        self.assertEqual('QPen', obj.typeName())

    def testQColor(self):
        obj = QVariant(QColor(Qt.red))
        self.assertEqual('QColor', obj.typeName())

    def testGlobalColor(self):
        obj = QVariant(Qt.red)
        # XXX: PyQt4 returns int instead of QColor like the C++ version
        self.assertEqual('QColor', obj.typeName())

    def testEnums(self):
        obj = QVariant(Qt.SolidLine)
        self.assertEqual('int', obj.typeName())

class QVariantQColorImplicitlyConvertion(unittest.TestCase):
    def testConversions(self):
        c1 = QColor(0, 0, 0)
        v = QVariant(c1)
        c2 = QColor(v)
        self.assertEqual(c1, c2)

class QVariantQPixmap(UsesQApplication):
    '''QVariant(QPixmap)'''

    def testBasic(self):
        '''QVariant(QPixmap)'''
        pixmap = QPixmap(10,20)
        pixmap.fill(Qt.blue)
        variant = QVariant(pixmap)

        self.assertEqual(variant.typeName(), "QPixmap")

    def testQObject(self):
        obj = QObject()
        v = QVariant(obj)
        self.assertEqual(v.typeName(), 'QObject*')

    def testQWidget(self):
        obj = QWidget()
        v = QVariant(obj)
        self.assertEqual(v.typeName(), 'QWidget*')

class MyColor(QColor):
    pass

class MyPrimitive(int):
    pass

class QVariantMess(unittest.TestCase):
    def testMyColor(self):
        c1 = MyColor()
        v = QVariant(c1)
        self.assertEqual(type(v.toPyObject()), MyColor)

    def testMyPrimitive(self):
        p = MyPrimitive(3)
        v = QVariant(p)
        self.assertNotEqual(v.type(), QVariant.Int)
        self.assertTrue(v.toPyObject() is p)

if __name__ == '__main__':
    unittest.main()

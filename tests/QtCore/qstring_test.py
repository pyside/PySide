#!/usr/bin/python
# -*- coding: utf-8 -*-
'''Test cases for QString'''

import unittest
import ctypes
import sys

from PySide.QtCore import *

class QStringConstructor(unittest.TestCase):
    '''Test case for QString constructors'''

    def testQStringDefault(self):
        obj = QObject()
        obj.setObjectName('foo')
        self.assertEqual(obj.objectName(), u'foo')
        obj.setObjectName(u'áâãà')
        self.assertEqual(obj.objectName(), u'áâãà')
        obj.setObjectName(None)
        self.assertEqual(obj.objectName(), u'')

class QStringImplicitConvertion(unittest.TestCase):
    '''Implicit conversions for QString'''

    def testQByteArray(self):
        '''QString implicitly conversion: QByteArray'''
        obj = QObject()
        obj.setObjectName(QByteArray('foobar'))
        self.assertEqual(obj.objectName(), u'foobar')


if __name__ == '__main__':
    unittest.main()

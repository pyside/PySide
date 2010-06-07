#!/usr/bin/python
# -*- coding: utf-8 -*-

'''Unit tests for QObject's tr and trUtf8 static methods.'''

import os
import unittest
from PySide.QtCore import QObject

#from helper import UsesQCoreApplication

class QObjectTrTest(unittest.TestCase):
    '''Test case to check if QObject tr and trUtf8 static methods could be treated as instance methods.'''

    def setUp(self):
        self.obj = QObject()

    def tearDown(self):
        del self.obj

    def testTrCommonCase(self):
        #Test common case for QObject.tr
        invar1 = 'test1'
        outvar1 = self.obj.tr(invar1)
        invar2 = 'test2'
        outvar2 = self.obj.tr(invar2, 'test comment')
        self.assertEqual((invar1, invar2), (outvar1, outvar2))

    def testTrAsInstanceMethod(self):
        #Test QObject.tr as instance
        invar1 = 'test1'
        outvar1 = QObject.tr(self.obj, invar1)
        invar2 = 'test2'
        outvar2 = QObject.tr(self.obj, invar2, 'test comment')
        self.assertEqual((invar1, invar2), (outvar1, outvar2))

    def testTrUtf8CommonCase(self):
        #Test common case for QObject.trUtf8
        invar1 = 'test1'
        outvar1 = self.obj.trUtf8(invar1)
        invar2 = 'test2'
        outvar2 = self.obj.trUtf8(invar2, 'test comment')
        self.assertEqual((invar1, invar2), (outvar1, outvar2))

    def testTrUtf8AsInstanceMethod(self):
        #Test QObject.trUtf8 as instance
        invar1 = 'test1'
        outvar1 = QObject.trUtf8(self.obj, invar1)
        invar2 = 'test2'
        outvar2 = QObject.trUtf8(self.obj, invar2, 'test comment')
        self.assertEqual((invar1, invar2), (outvar1, outvar2))

if __name__ == '__main__':
    unittest.main()


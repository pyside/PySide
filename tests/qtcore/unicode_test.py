#!/usr/bin/python
# -*- coding: utf-8 -*-

'''Unit tests for QString conversion to/from Python Unicode'''

import unittest

from PySide.QtCore import QObject

class UnicodeConversion(unittest.TestCase):
    '''Test case for QString to/from Python Unicode conversion'''

    def setUp(self):
        pass

    def tearDown(self):
        pass

    def testSetRegularStringRetrieveUnicode(self):
        #Set regular Python string retrieve unicode
        obj = QObject()
        obj.setObjectName('test')
        self.assertEqual(obj.objectName(), u'test')

    def testSetUnicodeRetrieveUnicode(self):
        #Set Python unicode string and retrieve unicode
        obj = QObject()
        obj.setObjectName(u'ümlaut')
        self.assertEqual(obj.objectName(), u'ümlaut')

if __name__ == '__main__':
    unittest.main()


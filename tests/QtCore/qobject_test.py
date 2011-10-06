#!/usr/bin/python
# -*- coding: utf-8 -*-
'''Test cases for QObject methods'''

import unittest
import py3kcompat as py3k

from PySide.QtCore import QObject

class ObjectNameCase(unittest.TestCase):
    '''Tests related to QObject object name'''

    def testSimple(self):
        #QObject.objectName(string)
        name = 'object1'
        obj = QObject()
        obj.setObjectName(name)

        self.assertEqual(name, obj.objectName())

    def testEmpty(self):
        #QObject.objectName('')
        name = ''
        obj = QObject()
        obj.setObjectName(name)

        self.assertEqual(name, obj.objectName())

    def testDefault(self):
        #QObject.objectName() default
        obj = QObject()
        self.assertEqual('', obj.objectName())

    def testUnicode(self):
        name = py3k.unicode_('não')
        #FIXME Strange error on upstream when using equal(name, obj)
        obj = QObject()
        obj.setObjectName(name)
        self.assertEqual(obj.objectName(), name)


if __name__ == '__main__':
    unittest.main()

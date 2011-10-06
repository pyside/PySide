#!/usr/bin/python
# -*- coding: utf-8 -*-
'''Test cases for QString'''

import unittest
import py3kcompat as py3k
from PySide.QtCore import QObject

class QStringConstructor(unittest.TestCase):
    '''Test case for QString constructors'''

    def testQStringDefault(self):
        obj = QObject()
        obj.setObjectName('foo')
        self.assertEqual(obj.objectName(), py3k.unicode_('foo'))
        obj.setObjectName(py3k.unicode_('áâãà'))
        self.assertEqual(obj.objectName(), py3k.unicode_('áâãà'))
        obj.setObjectName(None)
        self.assertEqual(obj.objectName(), py3k.unicode_(''))

if __name__ == '__main__':
    unittest.main()

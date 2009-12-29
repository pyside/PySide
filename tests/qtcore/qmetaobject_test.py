#!/usr/bin/python
# -*- coding: utf-8 -*-
'''Tests for static methos conflicts with class methods'''

import unittest

from PySide.QtCore import *

class Foo(QFile):
  pass

class qmetaobject_test(unittest.TestCase):
    def test_QMetaObject(self):
        qobj = QObject()
        qobj_metaobj = qobj.metaObject()
        self.assertEqual(qobj_metaobj.className(), "QObject")

        obj = QFile()
        m = obj.metaObject()
        self.assertEqual(m.className(), "QFile")
        self.assertNotEqual(m.methodCount(), qobj_metaobj.methodCount())

        obj = Foo()
        m = obj.metaObject()
        self.assertEqual(m.className(), "Foo")
        f = QFile()
        fm = f.metaObject()
        self.assertEqual(m.methodCount(), fm.methodCount())


if __name__ == '__main__':
    unittest.main()


#!/usr/bin/python
# -*- coding: utf-8 -*-
'''Tests for static methos conflicts with class methods'''

import unittest

from PySide.QtCore import *

class Foo(QFile):
  pass

class DynObject(QObject):
    def slot(self):
        pass

class qmetaobject_test(unittest.TestCase):
    """
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
    """        

    def test_DynamicSlotSignal(self):
        o = DynObject()
        o2 = QObject()

        o.connect(o2, SIGNAL("bars()"), o.slot)
        self.assertTrue(o2.metaObject().indexOfMethod("bars()") > -1)
        #self.assertTrue(o.metaObject().indexOfMethod("bar()") == -1)
        #self.assertTrue(o.metaObject().indexOfMethod("slot()") > -1)

        #slot_index = o.metaObject().indexOfMethod("slot()")

        #o.connect(o, SIGNAL("foo()"), o2, SIGNAL("bar()"))
        #signal_index = o.metaObject().indexOfMethod("foo()");

        #self.assert_(slot_index != signal_index)


if __name__ == '__main__':
    unittest.main()


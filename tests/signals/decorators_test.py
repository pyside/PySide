#!/usr/bin/env python

import sys
import unittest
import functools

from PySide.QtCore import *

class MyObject(QObject):
    def __init__(self, parent=None):
        QObject.__init__(self, parent)
        self._slotCalledCount = 0

    @Slot()
    def mySlot(self):
        self._slotCalledCount = self._slotCalledCount + 1

    @Slot(int)
    @Slot('QString')
    def mySlot2(self, arg0):
        self._slotCalledCount = self._slotCalledCount + 1

    @Slot(name='mySlot3')
    def foo(self):
        self._slotCalledCount = self._slotCalledCount + 1

    @Slot(unicode, int)
    def mySlot4(self, a, b):
        self._slotCalledCount = self._slotCalledCount + 1

    @Slot(result=int)
    def mySlot5(self):
        self._slotCalledCount = self._slotCalledCount + 1

class StaticMetaObjectTest(unittest.TestCase):

    def testSignalPropagation(self):
        o = MyObject()
        m = o.metaObject()
        self.assert_(m.indexOfSlot('mySlot()') > 0)
        self.assert_(m.indexOfSlot('mySlot2(int)') > 0)
        self.assert_(m.indexOfSlot('mySlot2(QString)') > 0)
        self.assert_(m.indexOfSlot('mySlot3()') > 0)
        self.assert_(m.indexOfSlot('mySlot4(QString,int)') > 0)

    def testEmission(self):
        o = MyObject()
        o.connect(SIGNAL("mySignal()"), o, SLOT("mySlot()"))
        o.emit(SIGNAL("mySignal()"))
        self.assert_(o._slotCalledCount == 1)

    def testResult(self):
        o = MyObject()
        mo = o.metaObject()
        i = mo.indexOfSlot('mySlot5()')
        m = mo.method(i)
        self.assertEqual(m.typeName(), "int")

if __name__ == '__main__':
    unittest.main()

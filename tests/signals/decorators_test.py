#!/usr/bin/env python

import unittest

from PySide.QtCore import QObject, Slot, SIGNAL, SLOT

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

    @Slot(str, int)
    def mySlot4(self, a, b):
        self._slotCalledCount = self._slotCalledCount + 1

    @Slot(result=int)
    def mySlot5(self):
        self._slotCalledCount = self._slotCalledCount + 1

    @Slot(result=QObject)
    def mySlot6(self):
        self._slotCalledCount = self._slotCalledCount + 1

class StaticMetaObjectTest(unittest.TestCase):

    def testSignalPropagation(self):
        o = MyObject()
        m = o.metaObject()
        self.assertTrue(m.indexOfSlot('mySlot()') > 0)
        self.assertTrue(m.indexOfSlot('mySlot2(int)') > 0)
        self.assertTrue(m.indexOfSlot('mySlot2(QString)') > 0)
        self.assertTrue(m.indexOfSlot('mySlot3()') > 0)
        self.assertTrue(m.indexOfSlot('mySlot4(QString,int)') > 0)

    def testEmission(self):
        o = MyObject()
        o.connect(SIGNAL("mySignal()"), o, SLOT("mySlot()"))
        o.emit(SIGNAL("mySignal()"))
        self.assertTrue(o._slotCalledCount == 1)

    def testResult(self):
        o = MyObject()
        mo = o.metaObject()
        i = mo.indexOfSlot('mySlot5()')
        m = mo.method(i)
        self.assertEqual(m.typeName(), "int")

    def testResultObject(self):
        o = MyObject()
        mo = o.metaObject()
        i = mo.indexOfSlot('mySlot6()')
        m = mo.method(i)
        self.assertEqual(m.typeName(), "QObject*")

class SlotWithoutArgs(unittest.TestCase):

    def testError(self):
        # It should be an error to call the slot without the
        # arguments, as just @Slot would end up in a slot
        # accepting argument functions
        self.assertRaises(TypeError, Slot, lambda: 3)

if __name__ == '__main__':
    unittest.main()

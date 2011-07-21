#!/usr/bin/env python

"""Tests covering signal emission and receiving to python slots"""

import unittest

from PySide.QtCore import QObject, SIGNAL
from helper import UsesQCoreApplication

class MyObject(QObject):
    def __init__(self, parent=None):
        QObject.__init__(self, parent)
        self._slotCalledCount = 0

    def mySlot(self):
        self._slotCalledCount = self._slotCalledCount + 1


class StaticMetaObjectTest(UsesQCoreApplication):

    def testSignalPropagation(self):
        o = MyObject()
        o2 = MyObject()

        # SIGNAL foo not created yet
        self.assertEqual(o.metaObject().indexOfSignal("foo()"), -1)

        o.connect(SIGNAL("foo()"), o2.mySlot)
        # SIGNAL foo create after connect
        self.assert_(o.metaObject().indexOfSignal("foo()") > 0)

        # SIGNAL does not propagate to others objects of the same type
        self.assertEqual(o2.metaObject().indexOfSignal("foo()"), -1)

        del o
        del o2
        o = MyObject()
        # The SIGNAL was destroyed with old objects
        self.assertEqual(o.metaObject().indexOfSignal("foo()"), -1)


    def testSharedSignalEmission(self):
        o = QObject()
        m = MyObject()

        o.connect(SIGNAL("foo2()"), m.mySlot)
        m.connect(SIGNAL("foo2()"), m.mySlot)
        o.emit(SIGNAL("foo2()"))
        self.assertEqual(m._slotCalledCount, 1)
        del o
        m.emit(SIGNAL("foo2()"))
        self.assertEqual(m._slotCalledCount, 2)

if __name__ == '__main__':
    unittest.main()

#!/usr/bin/env python

"""Tests covering signal emission and receiving to python slots"""

import sys
import unittest
import functools

from PySide.QtCore import *
from helper import BasicPySlotCase, UsesQCoreApplication

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

        m = o.metaObject()
        # SIGNAL foo not created yet
        self.assertEqual(m.indexOfSignal("foo()"), -1)

        o.connect(SIGNAL("foo()"), o2.mySlot)
        # SIGNAL foo create after connect
        self.assert_(m.indexOfSignal("foo()") > 0)

        m = o2.metaObject()
        # SIGNAL propagate to others objects of the same type
        self.assert_(m.indexOfSignal("foo()") > 0)

        del o
        # SIGNAL foo continues registered after deletion of original object
        self.assert_(m.indexOfSignal("foo()") > 0)

        del o2
        o = MyObject()
        m = o.metaObject()
        # new objects still have the SIGNAL foo registered
        self.assert_(m.indexOfSignal("foo()") > 0)


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

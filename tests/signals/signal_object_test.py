#!/usr/bin/env python

import sys
import unittest
import functools

from PySide.QtCore import *

class MyObject(QObject):
    sig1 = Signal()
    sig2 = Signal(int, name='rangeChanged')


    @Slot(int)
    def myRange(self, r):
        print "Range changed:", r


    def slot1(self):
        self._called = True



class SignalObjectTest(unittest.TestCase):

    def testsingleConnect(self):
        o = MyObject()
        o.sig1.connect(o.slot1)
        o.sig1.emit()
        self.assert_(o._called)

    def testSignatureParse(self):
        o = MyObject()
        o.sig2.connect(o.myRange)
        o.sig2.emit(10)


if __name__ == '__main__':
    unittest.main()

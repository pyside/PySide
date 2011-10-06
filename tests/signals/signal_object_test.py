#!/usr/bin/env python

import unittest

from PySide.QtCore import QTimer, Signal, QObject, Slot, Qt
from helper import UsesQCoreApplication

class MyObject(QTimer):
    sig1 = Signal()
    sig2 = Signal(int, name='rangeChanged')
    sig3 = Signal(int)
    sig4 = Signal((int,), (str,))
    sig5 = Signal((str,), (int,))
    sig6 = Signal(QObject)

    @Slot(int)
    def myRange(self, r):
        self._range = r

    def slot1(self):
        self._called = True

    def slotString(self, s):
        self._s = s

    def slotObject(self, o):
        self._o = o


class SignalObjectTest(UsesQCoreApplication):
    def cb(self):
        self._cb_called = True
        self.app.exit()

    def testsingleConnect(self):
        o = MyObject()
        o.sig1.connect(o.slot1)
        o.sig1.emit()
        self.assertTrue(o._called)

    def testSignalWithArgs(self):
        o = MyObject()
        o.sig3.connect(o.myRange)
        o.sig3.emit(10)
        self.assertEqual(o._range, 10)

    def testSignatureParse(self):
        o = MyObject()
        o.sig2.connect(o.myRange)
        o.sig2.emit(10)

    def testDictOperator(self):
        o = MyObject()
        o.sig4[str].connect(o.slotString)
        o.sig4[str].emit("PySide")
        self.assertEqual(o._s, "PySide")

    def testGeneretedSignal(self):
        o = MyObject()
        o.timeout.connect(self.cb)
        o.start(100)
        self.app.exec_()
        self.assertTrue(self._cb_called)

    def testConnectionType(self):
        o = MyObject()
        o.timeout.connect(self.cb, type=Qt.DirectConnection)
        o.start(100)
        self.app.exec_()
        self.assertTrue(self._cb_called)

    def testSignalWithSignal(self):
        o = MyObject()
        o.sig2.connect(o.myRange)
        o.sig5.connect(o.sig2)
        o.sig5[int].emit(10)
        self.assertEqual(o._range, 10)

    def testSignalWithObject(self):
        o = MyObject()
        o.sig6.connect(o.slotObject)
        arg = QObject()
        o.sig6.emit(arg)
        self.assertEqual(arg, o._o)

if __name__ == '__main__':
    unittest.main()

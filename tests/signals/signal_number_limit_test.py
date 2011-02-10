#!/usr/bin/env python
# -*- coding: utf-8 -*-

import unittest
from PySide import QtCore

class Emitter(QtCore.QObject):
    s1 = QtCore.Signal()
    s2 = QtCore.Signal()
    s3 = QtCore.Signal()
    s4 = QtCore.Signal()
    s5 = QtCore.Signal()
    s6 = QtCore.Signal()
    s7 = QtCore.Signal()
    s8 = QtCore.Signal()
    s9 = QtCore.Signal()
    s10 = QtCore.Signal()
    s11 = QtCore.Signal()
    s12 = QtCore.Signal()
    s13 = QtCore.Signal()
    s14 = QtCore.Signal()

class SignalNumberLimitTest(unittest.TestCase):
    def myCb(self):
        self._count += 1

    def testBug(self):
        e = Emitter()
        e.s1.connect(self.myCb)
        e.s2.connect(self.myCb)
        e.s3.connect(self.myCb)
        e.s4.connect(self.myCb)
        e.s5.connect(self.myCb)
        e.s6.connect(self.myCb)
        e.s7.connect(self.myCb)
        e.s8.connect(self.myCb)
        e.s9.connect(self.myCb)
        e.s10.connect(self.myCb)
        e.s11.connect(self.myCb)
        e.s12.connect(self.myCb)
        e.s13.connect(self.myCb)
        e.s14.connect(self.myCb)

        self._count = 0
        e.s1.emit()
        e.s2.emit()
        e.s3.emit()
        e.s4.emit()
        e.s5.emit()
        e.s6.emit()
        e.s7.emit()
        e.s8.emit()
        e.s9.emit()
        e.s10.emit()
        e.s11.emit()
        e.s12.emit()
        e.s13.emit()
        e.s14.emit()
        self.assertEqual(self._count, 14)

if __name__ == '__main__':
    unittest.main()

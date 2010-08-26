#!/usr/bin/env python
# -*- coding: utf-8 -*-

import unittest
from PySide import QtCore
from helper import UsesQCoreApplication

class DerivedDate(QtCore.QDate):
    def __init__(self,y,m,d):
        super(DerivedDate,self).__init__(y,m,d)

class Emitter(QtCore.QObject):
    dateSignal1 = QtCore.Signal(QtCore.QDate)
    dateSignal2 = QtCore.Signal(DerivedDate)
    tupleSignal = QtCore.Signal(tuple)

class SignaltoSignalTest(UsesQCoreApplication):
    def myCb(self, dt):
        self._dt = dt

    def testBug(self):
        e = Emitter()
        d = DerivedDate(2010,8,24)
        self._dt = None
        e.dateSignal1.connect(self.myCb)
        e.dateSignal1.emit(d)
        self.assertEqual(self._dt, d)

        self._dt = None
        e.dateSignal2.connect(self.myCb)
        e.dateSignal2.emit(d)
        self.assertEqual(self._dt, d)

        myTuple = (5, 6, 7)
        self._dt = None
        e.tupleSignal.connect(self.myCb)
        e.tupleSignal.emit(myTuple)
        self.assertEqual(myTuple, self._dt)

if __name__ == '__main__':
    unittest.main()


#!/usr/bin/env python
# -*- coding: utf-8 -*-

import unittest
import sys
from PySide.QtCore import QObject, SIGNAL

class Dummy(object):
    def __init__(self, parent):
        self._parent = parent

    def callback(self):
        self._called = True

class MultipleSlots(unittest.TestCase):
    def myCB(self):
        self._count += 1

    def testUnboundSignal(self):
        o = QObject()
        self._count  = 0
        for i in range(200):
            QObject.connect(o, SIGNAL("fire()"), lambda: self.myCB())

        o.emit(SIGNAL("fire()"))
        self.assertEqual(self._count, 200)

    def testDisconnectCleanup(self):
        for c in range(5):
            self._count = 0
            self._senders = []
            for i in range(200):
                o = QObject()
                QObject.connect(o, SIGNAL("fire()"), lambda: self.myCB())
                self._senders.append(o)
                o.emit(SIGNAL("fire()"))

            self.assertEqual(self._count, 200)

            #delete all senders will disconnect the signals
            self._senders = []

if __name__ == '__main__':
    unittest.main()



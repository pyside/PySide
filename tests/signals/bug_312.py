#!/usr/bin/env python
# -*- coding: utf-8 -*-

import unittest
import sys
from PySide.QtCore import QObject, SIGNAL

MAX_LOOPS = 5
MAX_OBJECTS = 200

class Dummy(object):
    def __init__(self, parent):
        self._parent = parent

    def callback(self):
        self._called = True

class MultipleSlots(unittest.TestCase):
    def myCB(self):
        self._count += 1

    """
    def testUnboundSignal(self):
        o = QObject()
        self._count  = 0
        for i in range(MAX_OBJECTS):
            QObject.connect(o, SIGNAL("fire()"), lambda: self.myCB())

        o.emit(SIGNAL("fire()"))
        self.assertEqual(self._count, MAX_OBJECTS)

    """
    def testDisconnectCleanup(self):
        for c in range(MAX_LOOPS):
            self._count = 0
            self._senders = []
            for i in range(MAX_OBJECTS):
                o = QObject()
                QObject.connect(o, SIGNAL("fire()"), lambda: self.myCB())
                self._senders.append(o)
                o.emit(SIGNAL("fire()"))

            self.assertEqual(self._count, MAX_OBJECTS)

            #delete all senders will disconnect the signals
            self._senders = []

if __name__ == '__main__':
    unittest.main()



#!/usr/bin/env python
# -*- coding: utf-8 -*-

import unittest
from PySide.QtCore import QObject, Signal

class ExtQObject(QObject):

    mySignal = Signal()

    def __init__(self):
        QObject.__init__(self)


class UserSignalTest(unittest.TestCase):

    def setUp(self):
        self.emitter = ExtQObject()
        self.counter = 0

    def tearDown(self):
        del self.emitter
        del self.counter

    def testConnectEmitDisconnect(self):

        def slot():
            self.counter += 1

        self.emitter.mySignal.connect(slot)

        self.assertEqual(self.counter, 0)
        self.emitter.mySignal.emit()
        self.assertEqual(self.counter, 1)
        self.emitter.mySignal.emit()
        self.assertEqual(self.counter, 2)

        self.emitter.mySignal.disconnect(slot)

        self.emitter.mySignal.emit()
        self.assertEqual(self.counter, 2)

#    def testConnectWithConfigureMethod(self):
#
#        def slot():
#            self.counter += 1
#
#        self.emitter.pyqtConfigure(mySignal=slot)
#        self.assertEqual(self.counter, 0)
#        self.emitter.mySignal.emit()
#        self.assertEqual(self.counter, 1)


if __name__ == '__main__':
    unittest.main()


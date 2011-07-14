#!/usr/bin/env python

import sys
import unittest
import PySide.QtCore as QtCore

class Signaller(QtCore.QObject):
    s1 = QtCore.Signal()
    s2 = QtCore.Signal()

class TestBug920(unittest.TestCase):

    def testIt(self):
        s = Signaller()
        s.s1.connect(self.onSignal)
        s.s2.connect(self.onSignal)
        self.assertTrue(s.s1.disconnect(self.onSignal))
        self.assertTrue(s.s2.disconnect(self.onSignal))

    def onSignal(self):
        pass


if __name__ == "__main__":
    unittest.main()

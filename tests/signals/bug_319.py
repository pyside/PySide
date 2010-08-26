#!/usr/bin/env python
# -*- coding: utf-8 -*-

import unittest
from PySide import QtCore
from helper import UsesQCoreApplication

class Listener(QtCore.QObject):
    def __init__(self):
        QtCore.QObject.__init__(self, None)
        self._phrase = []

    @QtCore.Slot(tuple)
    def listen(self, words):
        for w in words:
            self._phrase.append(w)

class Communicate(QtCore.QObject):
    # create a new signal on the fly and name it 'speak'
    speak = QtCore.Signal(tuple)

class SignaltoSignalTest(UsesQCoreApplication):
    def testBug(self):
        someone = Communicate()
        someone2 = Listener()
        # connect signal and slot
        someone.speak.connect(someone2.listen)
        # emit 'speak' signal
        talk = ("one","two","three")
        someone.speak.emit(talk)
        self.assertEqual(someone2._phrase, list(talk))

if __name__ == '__main__':
    unittest.main()


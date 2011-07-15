#!/usr/bin/env python

import unittest

import PySide.QtCore as QtCore
import PySide.QtGui as QtGui

from helper import TimedQApplication

class Signaller(QtCore.QObject):
    s1 = QtCore.Signal()
    s2 = QtCore.Signal()
    s3 = QtCore.Signal()

class Window(object):

    def __init__(self, s):
        self._window = QtGui.QMainWindow()
        self._window.setAttribute(QtCore.Qt.WA_DeleteOnClose, True)
        self._window.setWindowTitle("Demo!")

        self._s = s
        self._s.s1.connect(self._on_signal)
        self._s.s2.connect(self._on_signal)

    def show(self):
        self._window.show()

    def _on_signal(self):
        self._window.setWindowTitle("Signaled!")

class TestTimedApp(TimedQApplication):
    def testSignals(self):
        s = Signaller()
        w = Window(s)
        w.show()

        def midleFunction():
            def internalFunction():
                pass
            s.s3.connect(internalFunction)

        midleFunction()
        self.app.exec_()
        del w

        s.s1.emit()
        s.s2.emit()
        s.s3.emit()

if __name__ == '__main__':
    unittest.main()

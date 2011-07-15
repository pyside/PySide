#!/usr/bin/env python

import sys

import PySide.QtCore as QtCore
import PySide.QtGui as QtGui

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

    def _on_destroyed(self, obj = None):
        self._s.s1.disconnect(self._on_signal)
        self._s.s2.disconnect(self._on_signal)


if __name__ == "__main__":
    app = QtGui.QApplication([])

    s = Signaller()
    w = Window(s)
    w.show()

    def midleFunction():
        def internalFunction():
            pass
        s.s3.connect(internalFunction)

    midleFunction()
    val = app.exec_()
    del w

    s.s1.emit()
    s.s2.emit()
    s.s3.emit()

    sys.exit(val)

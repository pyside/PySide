# -*- coding: utf-8 -*-

''' Test the QShortcut constructor'''

import unittest
import sys

from PySide import QtGui, QtCore

class Foo(QtGui.QWidget):
    def __init__(self):
        QtGui.QWidget.__init__(self)
        self.ok = False
        self.copy = False

    def slot_of_foo(self):
        self.ok = True

    def slot_of_copy(self):
        self.copy = True

class MyShortcut(QtGui.QShortcut):
    def __init__(self, keys, wdg, slot):
        QtGui.QShortcut.__init__(self, keys, wdg, slot)

    def emit_signal(self):
        self.emit(QtCore.SIGNAL("activated()"))

class QAppPresence(unittest.TestCase):

    def testQShortcut(self):
        self.qapp = QtGui.QApplication([])
        f = Foo()

        self.sc = MyShortcut(QtGui.QKeySequence(QtCore.Qt.Key_Return), f, f.slot_of_foo)
        self.scstd = MyShortcut(QtGui.QKeySequence.Copy, f, f.slot_of_copy)
        QtCore.QTimer.singleShot(0, self.init);
        self.qapp.exec_()
        self.assertEquals(f.ok, True)
        self.assertEquals(f.copy, True)

    def init(self):
        self.sc.emit_signal();
        self.scstd.emit_signal();
        self.qapp.quit()

if __name__ == '__main__':
    unittest.main()

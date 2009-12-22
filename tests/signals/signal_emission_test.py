#!/usr/bin/env python

"""Tests covering signal emission and receiving to python slots"""

import sys
import unittest

from PySide.QtCore import QObject, SIGNAL, SLOT, QProcess, QTimeLine
from PySide.QtCore import QTimer, QThread

from helper import BasicPySlotCase, UsesQCoreApplication


class ArgsOnEmptySignal(UsesQCoreApplication):
    '''Trying to emit a signal without arguments passing some arguments'''

    def testArgsToNoArgsSignal(self):
        '''Passing arguments to a signal without arguments'''
        process = QProcess()
        self.assertRaises(TypeError, process.emit, SIGNAL('started()'), 42)


class MoreArgsOnEmit(UsesQCoreApplication):
    '''Trying to pass more args than needed to emit (signals with args)'''

    def testMoreArgs(self):
        '''Passing more arguments than needed'''
        process = QProcess()
        self.assertRaises(TypeError, process.emit, SIGNAL('finished(int)'), 55, 55)

class Dummy(QObject):
    '''Dummy class'''
    pass


class PythonSignalToCppSlots(UsesQCoreApplication):
    '''Connect python signals to C++ slots'''

    def testWithoutArgs(self):
        '''Connect python signal to QTimeLine.toggleDirection()'''
        timeline = QTimeLine()
        dummy = Dummy()
        QObject.connect(dummy, SIGNAL('dummy()'),
                        timeline, SLOT('toggleDirection()'))

        orig_dir = timeline.direction()
        dummy.emit(SIGNAL('dummy()'))
        new_dir = timeline.direction()

        if orig_dir == QTimeLine.Forward:
            self.assertEqual(new_dir, QTimeLine.Backward)
        else:
            self.assertEqual(new_dir, QTimeLine.Forward)

    def testWithArgs(self):
        '''Connect python signals to QTimeLine.setCurrentTime(int)'''
        timeline = QTimeLine()
        dummy = Dummy()

        QObject.connect(dummy, SIGNAL('dummy(int)'),
                        timeline, SLOT('setCurrentTime(int)'))

        current = timeline.currentTime()
        dummy.emit(SIGNAL('dummy(int)'), current+42)
        self.assertEqual(timeline.currentTime(), current+42)

class CppSignalsToCppSlots(UsesQCoreApplication):
    '''Connection between C++ slots and signals'''

    def testWithoutArgs(self):
        '''Connect QThread.started() to QTimeLine.togglePaused()'''
        thread = QThread()
        timeline = QTimeLine()

        QObject.connect(thread, SIGNAL('started()'),
                        timeline, SLOT('toggleDirection()'))
        QObject.connect(thread, SIGNAL('started()'),
                        self.exit_app_cb)

        orig_dir = timeline.direction()

        timer = QTimer.singleShot(1000, self.exit_app_cb) # Just for safety

        thread.start()
        self.app.exec_()
        thread.exit(0)
        thread.wait()

        new_dir = timeline.direction()

        if orig_dir == QTimeLine.Forward:
            self.assertEqual(new_dir, QTimeLine.Backward)
        else:
            self.assertEqual(new_dir, QTimeLine.Forward)


if __name__ == '__main__':
    unittest.main()

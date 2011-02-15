#!/usr/bin/env python

"""Tests covering signal emission and receiving to python slots"""

import sys
import unittest
import functools

from PySide.QtCore import QObject, SIGNAL, SLOT, QProcess, QTimeLine

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
        '''Connect QProcess.started() to QTimeLine.togglePaused()'''
        process = QProcess()
        timeline = QTimeLine()

        QObject.connect(process, SIGNAL('finished(int, QProcess::ExitStatus)'),
                        timeline, SLOT('toggleDirection()'))

        orig_dir = timeline.direction()

        process.start(sys.executable, ['-c', '"print 42"'])
        process.waitForFinished()

        new_dir = timeline.direction()

        if orig_dir == QTimeLine.Forward:
            self.assertEqual(new_dir, QTimeLine.Backward)
        else:
            self.assertEqual(new_dir, QTimeLine.Forward)

called = False
def someSlot(args=None):
    global called
    called = True

class DynamicSignalsToFuncPartial(UsesQCoreApplication):

    def testIt(self):
        global called
        called = False
        o = QObject()
        o.connect(o, SIGNAL("ASignal"), functools.partial(someSlot, "partial .."))
        o.emit(SIGNAL("ASignal"))
        self.assertTrue(called)

class EmitUnknownType(UsesQCoreApplication):
    def testIt(self):
        a = QObject()
        a.connect(SIGNAL('foobar(Dummy)'), lambda x: 42) # Just connect with an unknown type
        self.assertRaises(TypeError, a.emit, SIGNAL('foobar(Dummy)'), 22)

class EmitEnum(UsesQCoreApplication):
    """Test emission of enum arguments"""

    def slot(self, arg):
        self.arg = arg

    def testIt(self):
        self.arg = None
        p = QProcess()
        p.stateChanged.connect(self.slot)
        p.stateChanged.emit(QProcess.NotRunning)
        self.assertEqual(self.arg, QProcess.NotRunning)

if __name__ == '__main__':
    unittest.main()

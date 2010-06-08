#!/usr/bin/env python

'''Connecting lambda to signals'''

import sys
import unittest

from PySide.QtCore import QObject, SIGNAL, QProcess

from helper import UsesQCoreApplication


class Dummy(QObject):

    def __init__(self, *args):
        super(Dummy, self).__init__(*args)


class BasicCase(unittest.TestCase):

    def testSimplePythonSignalNoArgs(self):
        #Connecting a lambda to a simple python signal without arguments
        obj = Dummy()
        QObject.connect(obj, SIGNAL('foo()'),
                        lambda: setattr(obj, 'called', True))
        obj.emit(SIGNAL('foo()'))
        self.assert_(obj.called)

    def testSimplePythonSignal(self):
        #Connecting a lambda to a simple python signal witharguments
        obj = Dummy()
        arg = 42
        QObject.connect(obj, SIGNAL('foo(int)'),
                        lambda x: setattr(obj, 'arg', 42))
        obj.emit(SIGNAL('foo(int)'), arg)
        self.assertEqual(obj.arg, arg)


class QtSigLambda(UsesQCoreApplication):

    qapplication = True

    def testNoArgs(self):
        '''Connecting a lambda to a signal without arguments'''
        proc = QProcess()
        dummy = Dummy()
        QObject.connect(proc, SIGNAL('started()'),
                        lambda: setattr(dummy, 'called', True))
        proc.start(sys.executable, ['-c', '""'])
        proc.waitForFinished()
        self.assert_(dummy.called)

    def testWithArgs(self):
        '''Connecting a lambda to a signal with arguments'''
        proc = QProcess()
        dummy = Dummy()
        QObject.connect(proc, SIGNAL('finished(int)'),
                        lambda x: setattr(dummy, 'called', x))
        proc.start(sys.executable, ['-c', '""'])
        proc.waitForFinished()
        self.assertEqual(dummy.called, proc.exitCode())


if __name__ == '__main__':
    unittest.main()

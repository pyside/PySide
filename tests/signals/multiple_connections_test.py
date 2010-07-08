
import sys
import unittest
from functools import partial

from PySide.QtCore import QObject, SIGNAL, QProcess

from helper import BasicPySlotCase, UsesQCoreApplication


class MultipleSignalConnections(unittest.TestCase):
    '''Base class for multiple signal connection testing'''

    def run_many(self, sender, signal, emitter, receivers, args=None):
        """Utility method to connect a list of receivers to a signal.
        sender - QObject that will emit the signal
        signal - string with the signal signature
        emitter - the callable that will trigger the signal
        receivers - list of BasicPySlotCase instances
        args - tuple with the arguments to be sent.
        """

        if args is None:
            args = tuple()
        for rec in receivers:
            rec.setUp()
            self.assert_(QObject.connect(sender, SIGNAL(signal), rec.cb))
            rec.args = tuple(args)

        emitter(*args)

        for rec in receivers:
            self.assert_(rec.called)


class PythonMultipleSlots(UsesQCoreApplication, MultipleSignalConnections):
    '''Multiple connections to python signals'''

    def testPythonSignal(self):
        """Multiple connections to a python signal (short-circuit)"""

        class Dummy(QObject):
            pass

        sender = Dummy()
        receivers = [BasicPySlotCase() for x in range(10)]
        self.run_many(sender, 'foobar', partial(sender.emit,SIGNAL('foobar')), receivers, (0, ))


class QProcessMultipleSlots(UsesQCoreApplication, MultipleSignalConnections):
    '''Multiple connections to QProcess signals'''

    def testQProcessStarted(self):
        '''Multiple connections to QProcess.started()'''
        sender = QProcess()
        receivers = [BasicPySlotCase() for x in range(10)]

        def start_proc(*args):
            sender.start(sys.executable, ['-c', '""'])
            sender.waitForFinished()

        self.run_many(sender, 'started()', start_proc, receivers)

    def testQProcessFinished(self):
        '''Multiple connections to QProcess.finished(int)'''
        sender = QProcess()
        receivers = [BasicPySlotCase() for x in range(10)]

        def start_proc(*args):
            sender.start(sys.executable, ['-c', '""'])
            sender.waitForFinished()

        self.run_many(sender, 'finished(int)', start_proc, receivers, (0,))

if __name__ == '__main__':
    unittest.main()

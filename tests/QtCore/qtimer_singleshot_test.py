#!/usr/bin/python

'''Test cases for QTimer.singleShot'''

import unittest

from PySide.QtCore import QObject, QTimer, QCoreApplication, Signal
from helper import UsesQCoreApplication

class WatchDog(QObject):
    '''Exits the QCoreApplication main loop after sometime.'''

    def __init__(self, watched):
        QObject.__init__(self)
        self.times_called = 0
        self.watched = watched

    def timerEvent(self, evt):
        self.times_called += 1
        if self.times_called == 20:
            self.watched.exit_app_cb()

class TestSingleShot(UsesQCoreApplication):
    '''Test case for QTimer.singleShot'''

    def setUp(self):
        #Acquire resources
        UsesQCoreApplication.setUp(self)
        self.watchdog = WatchDog(self)
        self.called = False

    def tearDown(self):
        #Release resources
        del self.watchdog
        del self.called
        UsesQCoreApplication.tearDown(self)

    def callback(self):
        self.called = True
        self.app.quit()

    def testSingleShot(self):
        QTimer.singleShot(100, self.callback)
        self.app.exec_()
        self.assert_(self.called)

class SigEmitter(QObject):

    sig1 = Signal()


class TestSingleShotSignal(UsesQCoreApplication):
    '''Test case for QTimer.singleShot connecting to signals'''

    def setUp(self):
        UsesQCoreApplication.setUp(self)
        self.watchdog = WatchDog(self)
        self.called = False

    def tearDown(self):
        del self.watchdog
        del self.called
        UsesQCoreApplication.tearDown(self)

    def callback(self):
        self.called = True
        self.app.quit()

    def testSingleShotSignal(self):
        emitter = SigEmitter()
        emitter.sig1.connect(self.callback)
        QTimer.singleShot(100, emitter.sig1)
        self.app.exec_()
        self.assert_(self.called)

if __name__ == '__main__':
    unittest.main()



'''Test case for timeout() signals from QTimer object.'''

import unittest
import os
import sys
from tempfile import mkstemp
from PySide.QtCore import QObject, QTimer, SIGNAL
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


class TestTimeoutSignal(UsesQCoreApplication):
    '''Test case to check if the signals are really being caught'''

    def setUp(self):
        #Acquire resources
        UsesQCoreApplication.setUp(self)
        self.watchdog = WatchDog(self)
        self.timer = QTimer()
        self.called = False

    def tearDown(self):
        #Release resources
        del self.watchdog
        del self.timer
        del self.called
        UsesQCoreApplication.tearDown(self)

    def callback(self, *args):
        #Default callback
        self.called = True

    def testTimeoutSignal(self):
        #Test the QTimer timeout() signal
        refCount = sys.getrefcount(self.timer)
        QObject.connect(self.timer, SIGNAL('timeout()'), self.callback)
        self.timer.start(4)
        self.watchdog.startTimer(10)

        self.app.exec_()

        self.assert_(self.called)
        self.assertEqual(sys.getrefcount(self.timer), refCount)

if __name__ == '__main__':
    unittest.main()


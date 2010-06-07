#!/usr/bin/python
'''Test case for QObject.timerEvent overloading'''

import unittest
from time import sleep
from PySide.QtCore import QObject, QCoreApplication

from helper import UsesQCoreApplication

class Dummy(QObject):

    def __init__(self, app):
        super(Dummy, self).__init__()
        self.times_called = 0
        self.app = app

    def timerEvent(self, event):
        QObject.timerEvent(self, event)
        event.accept()
        self.times_called += 1

        if self.times_called == 5:
            self.app.exit(0)

class QObjectTimerEvent(UsesQCoreApplication):

    def setUp(self):
        #Acquire resources
        super(QObjectTimerEvent, self).setUp()

    def tearDown(self):
        #Release resources
        super(QObjectTimerEvent, self).tearDown()

    def testTimerEvent(self):
        #QObject.timerEvent overloading
        obj = Dummy(self.app)
        timer_id = obj.startTimer(200)
        self.app.exec_()
        obj.killTimer(timer_id)
        self.assertEqual(obj.times_called, 5)

if __name__ == '__main__':
    unittest.main()

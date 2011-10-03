#!/usr/bin/python
'''Test case for QObject.childEvent and QTimer.childEvent overloading'''

import unittest
from time import sleep
from PySide.QtCore import QObject, QTimer, QCoreApplication

from helper import UsesQCoreApplication

class ExtQObject(QObject):
    def __init__(self):
        QObject.__init__(self)
        self.child_event_received = False

    def childEvent(self, event):
        QObject.childEvent(self, event)
        self.child_event_received = True

class ExtQTimer(QTimer):
    def __init__(self):
        QTimer.__init__(self)
        self.child_event_received = False

    def childEvent(self, event):
        QTimer.childEvent(self, event)
        self.child_event_received = True


class TestChildEvent(UsesQCoreApplication):
    '''Test case for QObject::childEvent and QTimer::childEvent'''

    def setUp(self):
        UsesQCoreApplication.setUp(self)

    def tearDown(self):
        UsesQCoreApplication.tearDown(self)

    def testQObject(self):
        parent = ExtQObject()
        child = QObject()
        child.setParent(parent)
        self.assertTrue(parent.child_event_received)

    def testQTimer(self):
        parent = ExtQTimer()
        child = QObject()
        child.setParent(parent)
        self.assert_(parent.child_event_received)

if __name__ == '__main__':
    unittest.main()


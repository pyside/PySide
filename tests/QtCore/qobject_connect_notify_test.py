# -*- coding: utf-8 -*-

''' Test case for QObject::connectNotify()'''

import unittest
from PySide.QtCore import *
from helper import UsesQCoreApplication

def cute_slot():
    pass

class Obj(QObject):
    def __init__(self):
        QObject.__init__(self)
        self.con_notified = False
        self.dis_notified = False
        self.signal = ""

    def connectNotify(self, signal):
        self.con_notified = True
        self.signal = signal

    def disconnectNotify(self, signal):
        self.dis_notified = True

    def reset(self):
        self.con_notified = False
        self.dis_notified = False

class TestQObjectConnectNotify(UsesQCoreApplication):
    '''Test case for QObject::connectNotify'''
    def setUp(self):
        UsesQCoreApplication.setUp(self)
        self.called = False             

    def tearDown(self):
        UsesQCoreApplication.tearDown(self)

    def testBasic(self):
        sender = Obj()
        receiver = QObject()
        sender.connect(SIGNAL("destroyed()"), receiver, SLOT("deleteLater()"))
        self.assert_(sender.con_notified)
        self.assertEqual(sender.signal, SIGNAL("destroyed()"))
        sender.disconnect(SIGNAL("destroyed()"), receiver, SLOT("deleteLater()"))
        self.assert_(sender.dis_notified)

    def testPySignal(self):
        sender = Obj()
        receiver = QObject()
        sender.connect(SIGNAL("foo()"), receiver, SLOT("deleteLater()"))
        self.assert_(sender.con_notified)
        sender.disconnect(SIGNAL("foo()"), receiver, SLOT("deleteLater()"))
        self.assert_(sender.dis_notified)

    def testPySlots(self):
        sender = Obj()
        receiver = QObject()
        sender.connect(SIGNAL("destroyed()"), cute_slot)
        self.assert_(sender.con_notified)
        sender.disconnect(SIGNAL("destroyed()"), cute_slot)
        self.assert_(sender.dis_notified)

    def testpyAll(self):
        sender = Obj()
        receiver = QObject()
        sender.connect(SIGNAL("foo()"), cute_slot)
        self.assert_(sender.con_notified)
        sender.disconnect(SIGNAL("foo()"), cute_slot)
        self.assert_(sender.dis_notified)

if __name__ == '__main__':
    unittest.main()

# -*- coding: utf-8 -*-

'''Test case for signal signature received by QObject::connectNotify().'''

import unittest
from PySide.QtCore import *
from helper import UsesQCoreApplication

class Obj(QObject):
    def __init__(self):
        QObject.__init__(self)
        self.signal = ''

    def connectNotify(self, signal):
        self.signal = signal

def callback(arg=None):
    pass

class TestConnectNotifyWithNewStyleSignals(UsesQCoreApplication):
    '''Test case for signal signature received by QObject::connectNotify().'''

    def testOldStyle(self):
        sender = Obj()
        receiver = QObject()
        sender.connect(SIGNAL('destroyed()'), receiver, SLOT('deleteLater()'))
        self.assertEqual(sender.signal, SIGNAL('destroyed()'))

    def testOldStyleWithPythonCallback(self):
        sender = Obj()
        sender.connect(SIGNAL('destroyed()'), callback)
        self.assertEqual(sender.signal, SIGNAL('destroyed()'))

    def testNewStyle(self):
        sender = Obj()

        sender.destroyed.connect(callback)
        self.assertEqual(sender.signal, SIGNAL('destroyed()'))

        sender.destroyed[QObject].connect(callback)
        self.assertEqual(sender.signal, SIGNAL('destroyed(QObject*)'))

if __name__ == '__main__':
    unittest.main()


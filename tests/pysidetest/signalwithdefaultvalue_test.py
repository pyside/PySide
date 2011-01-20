#!/usr/bin/python

import unittest
from testbinding import TestObject
from PySide.QtCore import QObject, SIGNAL

'''Tests the behaviour of signals with default values.'''

class SignalWithDefaultValueTest(unittest.TestCase):

    def setUp(self):
        self.obj = TestObject(0)
        self.void_called = False
        self.bool_called = False

    def tearDown(self):
        del self.obj
        del self.void_called
        del self.bool_called

    def testConnectNewStyleEmitVoidSignal(self):
        def callbackVoid():
            self.void_called = True
        def callbackBool(value):
            self.bool_called = True
        self.obj.signalWithDefaultValue.connect(callbackVoid)
        self.obj.signalWithDefaultValue[bool].connect(callbackBool)
        self.obj.emitSignalWithDefaultValue_void()
        self.assert_(self.void_called)
        self.assert_(self.bool_called)

    def testConnectNewStyleEmitBoolSignal(self):
        def callbackVoid():
            self.void_called = True
        def callbackBool(value):
            self.bool_called = True
        self.obj.signalWithDefaultValue.connect(callbackVoid)
        self.obj.signalWithDefaultValue[bool].connect(callbackBool)
        self.obj.emitSignalWithDefaultValue_bool()
        self.assert_(self.void_called)
        self.assert_(self.bool_called)

    def testConnectOldStyleEmitVoidSignal(self):
        def callbackVoid():
            self.void_called = True
        def callbackBool(value):
            self.bool_called = True
        QObject.connect(self.obj, SIGNAL('signalWithDefaultValue()'), callbackVoid)
        QObject.connect(self.obj, SIGNAL('signalWithDefaultValue(bool)'), callbackBool)
        self.obj.emitSignalWithDefaultValue_void()
        self.assert_(self.void_called)
        self.assert_(self.bool_called)

    def testConnectOldStyleEmitBoolSignal(self):
        def callbackVoid():
            self.void_called = True
        def callbackBool(value):
            self.bool_called = True
        QObject.connect(self.obj, SIGNAL('signalWithDefaultValue()'), callbackVoid)
        QObject.connect(self.obj, SIGNAL('signalWithDefaultValue(bool)'), callbackBool)
        self.obj.emitSignalWithDefaultValue_bool()
        self.assert_(self.void_called)
        self.assert_(self.bool_called)

if __name__ == '__main__':
    unittest.main()


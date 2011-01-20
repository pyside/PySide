#!/usr/bin/python

import unittest
from testbinding import TestObject
from PySide.QtCore import QObject, SIGNAL

'''Tests the behaviour of signals with default values when emitted from Python.'''

class SignalEmissionFromPython(unittest.TestCase):

    def setUp(self):
        self.obj1 = TestObject(0)
        self.obj2 = TestObject(0)
        self.one_called = 0
        self.two_called = 0

    def tearDown(self):
        del self.obj1
        del self.obj2
        del self.one_called
        del self.two_called

    def testConnectNewStyleEmitVoidSignal(self):
        def callbackOne():
            self.one_called += 1
            self.obj2.signalWithDefaultValue.emit()
        def callbackTwo():
            self.two_called += 1
        self.obj1.signalWithDefaultValue.connect(callbackOne)
        self.obj2.signalWithDefaultValue.connect(callbackTwo)
        self.obj1.emitSignalWithDefaultValue_void()
        self.obj2.emitSignalWithDefaultValue_void()
        self.assertEqual(self.one_called, 1)
        self.assertEqual(self.two_called, 2)

    def testConnectOldStyleEmitVoidSignal(self):
        def callbackOne():
            self.one_called += 1
            self.obj2.signalWithDefaultValue.emit()
        def callbackTwo():
            self.two_called += 1
        QObject.connect(self.obj1, SIGNAL('signalWithDefaultValue()'), callbackOne)
        QObject.connect(self.obj2, SIGNAL('signalWithDefaultValue()'), callbackTwo)
        self.obj1.emitSignalWithDefaultValue_void()
        self.obj2.emitSignalWithDefaultValue_void()
        self.assertEqual(self.one_called, 1)
        self.assertEqual(self.two_called, 2)

    def testConnectNewStyleEmitBoolSignal(self):
        def callbackOne():
            self.one_called += 1
            self.obj2.signalWithDefaultValue[bool].emit(True)
        def callbackTwo():
            self.two_called += 1
        self.obj1.signalWithDefaultValue.connect(callbackOne)
        self.obj2.signalWithDefaultValue.connect(callbackTwo)
        self.obj1.emitSignalWithDefaultValue_void()
        self.obj2.emitSignalWithDefaultValue_void()
        self.assertEqual(self.one_called, 1)
        self.assertEqual(self.two_called, 2)

    def testConnectOldStyleEmitBoolSignal(self):
        def callbackOne():
            self.one_called += 1
            self.obj2.signalWithDefaultValue[bool].emit(True)
        def callbackTwo():
            self.two_called += 1
        QObject.connect(self.obj1, SIGNAL('signalWithDefaultValue()'), callbackOne)
        QObject.connect(self.obj2, SIGNAL('signalWithDefaultValue()'), callbackTwo)
        self.obj1.emitSignalWithDefaultValue_void()
        self.obj2.emitSignalWithDefaultValue_void()
        self.assertEqual(self.one_called, 1)
        self.assertEqual(self.two_called, 2)



if __name__ == '__main__':
    unittest.main()


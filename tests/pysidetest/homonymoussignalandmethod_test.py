#!/usr/bin/python

import unittest
from testbinding import TestObject

'''Tests the behaviour of homonymous signals and slots.'''

class HomonymousSignalAndMethodTest(unittest.TestCase):

    def setUp(self):
        self.value = 123
        self.called = False
        self.obj = TestObject(self.value)

    def tearDown(self):
        del self.value
        del self.called
        del self.obj

    def testIdValueSignalEmission(self):
        def callback(idValue):
            self.assertEqual(idValue, self.value)
        self.obj.idValue.connect(callback)
        self.obj.emitIdValueSignal()

    def testStaticMethodDoubleSignalEmission(self):
        def callback():
            self.called = True
        self.obj.staticMethodDouble.connect(callback)
        self.obj.emitStaticMethodDoubleSignal()
        self.assert_(self.called)

    def testSignalNotCallable(self):
        self.assertRaises(TypeError, self.obj.justASignal)

    def testCallingInstanceMethodWithArguments(self):
        self.assertRaises(TypeError, TestObject.idValue, 1)

    def testCallingInstanceMethodWithoutArguments(self):
        self.assertRaises(TypeError, TestObject.idValue)

    def testHomonymousSignalAndMethod(self):
        self.assertEqual(self.obj.idValue(), self.value)

    def testHomonymousSignalAndStaticMethod(self):
        self.assertEqual(TestObject.staticMethodDouble(3), 6)

    def testHomonymousSignalAndStaticMethodFromInstance(self):
        self.assertEqual(self.obj.staticMethodDouble(4), 8)

if __name__ == '__main__':
    unittest.main()


#!/usr/bin/python

import unittest
from PySide.QtCore import QObject
from testbinding import TestObject

class Receiver(QObject):
    def __init__(self):
        QObject.__init__(self)
        self.called = False

    def ReceiverDecorator(func):
        def decoratedFunction(self, *args, **kw):
            func(self, *args, **kw)
        return decoratedFunction

    # This method with the same name of the internal decorated function
    # is here to test the binding capabilities.
    def decoratedFunction(self):
        pass

    @ReceiverDecorator
    def slot(self):
        self.called = True


class DecoratedSlotTest(unittest.TestCase):

    def testCallingOfDecoratedSlot(self):
        obj = TestObject(0)
        receiver = Receiver()
        obj.staticMethodDouble.connect(receiver.slot)
        obj.emitStaticMethodDoubleSignal()
        self.assert_(receiver.called)


if __name__ == '__main__':
    unittest.main()


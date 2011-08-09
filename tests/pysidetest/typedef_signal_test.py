
import unittest

from PySide.QtCore import QObject
from testbinding import TestObject

class Receiver(QObject):

    def __init__(self):
        QObject.__init__(self)
        self.received = None

    def slot(self, value):
        self.received = value

class TypedefSignal(unittest.TestCase):

    def testTypedef(self):
        obj = TestObject(0)
        receiver = Receiver()

        obj.signalWithTypedefValue.connect(receiver.slot)
        obj.emitSignalWithTypedefValue(2)
        self.assertEqual(receiver.received.value, 2)

if __name__ == '__main__':
    unittest.main()

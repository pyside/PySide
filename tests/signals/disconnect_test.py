import unittest
from PySide.QtCore import *

class Foo(QObject):
    bar = Signal()

class TestDisconnect(unittest.TestCase):
    def theSlot1(self):
        self.called1 = True

    def theSlot2(self):
        self.called2 = True

    def testIt(self):
        self.called1 = False
        self.called2 = False
        f = Foo()
        f.bar.connect(self.theSlot1)
        f.bar.connect(self.theSlot2)
        f.bar.emit()
        self.assertTrue(self.called1)
        self.assertTrue(self.called2)

        self.called1 = False
        self.called2 = False
        f.bar.disconnect()
        f.bar.emit()
        self.assertFalse(self.called1)
        self.assertFalse(self.called2)

if __name__ == '__main__':
    unittest.main()

import unittest

from PySide.QtCore import QObject, Signal
o = QObject()
class MyObject(QObject):
    s = Signal(int)

class CheckSignalType(unittest.TestCase):
    def testSignal(self):
        self.assertTrue(isinstance(QObject.destroyed, Signal))
        self.assertEqual(type(QObject.destroyed), Signal)

        self.assertEqual(type(o.destroyed).__name__, "SignalInstance")
        self.assertNotEqual(type(o.destroyed), Signal)

        self.assertTrue(isinstance(o.destroyed, Signal))
        self.assertTrue(isinstance(MyObject.s, Signal))
        self.assertFalse(isinstance(int, Signal))

if __name__ == '__main__':
    unittest.main()

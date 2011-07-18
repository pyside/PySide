import unittest

from PySide.QtCore import QObject, Signal
o = QObject()

class CheckSignalType(unittest.TestCase):
    def testSignal(self):
        self.assertTrue(isinstance(QObject.destroyed, Signal))
        self.assertEqual(type(QObject.destroyed), Signal)

        self.assertEqual(type(o.destroyed).__name__, "SignalInstance")
        self.assertNotEqual(type(o.destroyed), Signal)

if __name__ == '__main__':
    unittest.main()

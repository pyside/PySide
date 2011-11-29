''' unit test for BUG #1069 '''

from PySide import QtCore
import unittest

class QDataStreamOpOverloadTestCase(unittest.TestCase):
    def setUp(self):
        self.ba = QtCore.QByteArray()
        self.stream = QtCore.QDataStream(self.ba, QtCore.QIODevice.WriteOnly)

    def testIt(self):
        self.stream << "hello"
        ok = False
        for c in self.ba:
            if c != b'\x00':
                ok = True
                break

        self.assertEqual(ok, True)

if __name__ == "__main__":
    unittest.main()

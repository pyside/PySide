import unittest
import py3kcompat as py3k
from PySide.QtCore import QIODevice, QTextStream


class MyIODevice (QIODevice):
    def readData(self, amount):
        return py3k.b("\0a" * int(amount/2))

    def readLineData(self, maxSize):
        return py3k.b("\0b" * 4)

    def atEnd(self):
        return False

class TestBug944 (unittest.TestCase):

    def testIt(self):
        device = MyIODevice()
        device.open(QIODevice.ReadOnly)
        s = QTextStream(device)
        self.assertEqual(s.read(4), "\0a\0a")
        self.assertEqual(device.readLine(), "\0b\0b\0b\0b")

if __name__ == "__main__":
    unittest.main()

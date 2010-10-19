import unittest

from PySide.QtCore import *

class MyDevice(QIODevice):
    def __init__(self, txt):
        QIODevice.__init__(self)
        self.txt = txt
        self.ptr = 0

    def readData(self, size):
        size = min(len(self.txt) - self.ptr, size)
        retval = self.txt[self.ptr:size]
        self.ptr += size
        return retval

class QIODeviceTest(unittest.TestCase):

    def testIt(self):
        device = MyDevice("hello world\nhello again")
        device.open(QIODevice.ReadOnly)

        s = QTextStream(device)
        self.assertEqual(s.readLine(), "hello world")
        self.assertEqual(s.readLine(), "hello again")

if __name__ == '__main__':
    unittest.main()

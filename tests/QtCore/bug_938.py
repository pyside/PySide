import unittest
from PySide.QtCore import *

class TestBug938 (unittest.TestCase):

    def testIt(self):
        b = QBuffer()
        b.open(QBuffer.WriteOnly)
        b.write("\x0023\x005")
        b.close()
        self.assertEqual(b.buffer().size(), 5)

if __name__ == '__main__':
    unittest.main()

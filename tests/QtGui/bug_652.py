import unittest
from PySide.QtGui import *

class MyData(QTextBlockUserData):
    def __init__(self, data):
        QTextBlockUserData.__init__(self)
        self.data = data

    def getMyNiceData(self):
        return self.data

class TestBug652(unittest.TestCase):
    """Segfault when using QTextBlock::setUserData due to missing ownership transfer"""
    def testIt(self):
        td = QTextDocument()
        tc = QTextCursor(td)
        tc.insertText("Hello world")
        heyHo = "hey ho!"
        tc.block().setUserData(MyData(heyHo))
        self.assertEqual(type(tc.block().userData()), MyData)
        self.assertEqual(tc.block().userData().getMyNiceData(), heyHo)

        del tc
        tc = QTextCursor(td)
        blk = tc.block()
        self.assertEqual(type(blk.userData()), MyData)
        self.assertEqual(blk.userData().getMyNiceData(), heyHo)

if __name__ == "__main__":
    unittest.main()
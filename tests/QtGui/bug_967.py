import unittest
from PySide.QtGui import *

class TestBug967 (unittest.TestCase):

    def callback(self, arg):
        self.arg = arg

    def testIt(self):
        self.arg = None
        app = QApplication([])
        obj = QComboBox()
        obj.currentIndexChanged.connect(self.callback)
        obj.currentIndexChanged.emit(5)
        self.assertEqual(self.arg, 5)

if __name__ == "__main__":
    unittest.main()

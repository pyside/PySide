import sys
from PySide.QtGui import QLineEdit, QApplication
import unittest


class Bug589(unittest.TestCase):
    def testWrongSignature(self):
        text = QLineEdit("PySide bug 632")
        a = b = c = d = 0
        self.assertRaises(TypeError, text.getTextMargins, (a, b, c, d))

    def testTupleReturn(self):
        text = QLineEdit("PySide bug 632")
        text.setTextMargins(10, 20, 30, 40)
        (a, b, c, d) = text.getTextMargins()
        self.assert_((a, b, c, d), (10, 20, 30, 40))

if __name__ == "__main__":
   app = QApplication(sys.argv)
   unittest.main()

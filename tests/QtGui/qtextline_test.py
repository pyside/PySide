
import unittest

from PySide.QtGui import QTextLayout
from helper import UsesQApplication

class QTextLineTest(UsesQApplication):

    def testCursorToX(self):
        textLayout = QTextLayout()
        textLayout.beginLayout()
        line = textLayout.createLine()
        self.assert_(line.isValid())
        x, cursorPos = line.cursorToX(0)
        self.assertEqual(type(x), float)
        self.assertEqual(type(cursorPos), int)
        x, cursorPos = line.cursorToX(1)
        self.assertEqual(type(x), float)
        self.assertEqual(type(cursorPos), int)

if __name__ == '__main__':
    unittest.main()


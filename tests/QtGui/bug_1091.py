''' unit test for BUG #1091 '''

import unittest
from PySide import QtGui

class QPainterTestCase(unittest.TestCase):
    def testIt(self):
        self.assertTrue("PixmapFragment" in dir(QtGui.QPainter))
        self.assertTrue("drawPixmapFragments" in dir(QtGui.QPainter))

if __name__ == "__main__":
    unittest.main()

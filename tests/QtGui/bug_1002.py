import unittest
import sys
from PySide.QtGui import QWidget, QPushButton

from helper import UsesQApplication

class TestBug1002 (UsesQApplication):
    def testReturnWindow(self):
        widget = QWidget()
        button = QPushButton(widget)
        self.assertEqual(sys.getrefcount(widget), 2)
        window = button.window()
        self.assertEqual(sys.getrefcount(widget), 3)
        self.assertEqual(sys.getrefcount(window), 3)

        del widget

if __name__ == '__main__':
    unittest.main()

import unittest
from PySide.QtGui import QApplication

class TestBug998 (unittest.TestCase):
    def testNoFocusWindow(self):
        widget = QApplication.focusWidget()
        self.assertTrue(widget == None)

if __name__ == '__main__':
    unittest.main()


''' Test bug 243: http://bugs.openbossa.org/show_bug.cgi?id=243'''

import unittest
import sys

from PySide.QtGui import QApplication, QMainWindow, QLayout

class QAppPresence(unittest.TestCase):

    def testBug(self):
        app = QApplication(sys.argv)
        window = QMainWindow()
        l = window.layout()
        self.assert_(isinstance(l, QLayout))

if __name__ == '__main__':
    unittest.main()

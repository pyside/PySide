'''Test for Bug 630 - Fails to resolve overload for QCursor(QBitmap, QBitmap, int, int)
http://bugs.openbossa.org/show_bug.cgi?id=630
'''

import unittest
from PySide.QtGui import QBitmap, QCursor, QPixmap
from helper import UsesQApplication

class TestQCursor(UsesQApplication):
    def testQCursorConstructor(self):
        bmp = QBitmap(16, 16)
        cursor = QCursor(bmp, bmp, 16, 16)

if __name__ == '__main__':
    unittest.main()


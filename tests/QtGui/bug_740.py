import unittest

from helper import UsesQApplication
from PySide.QtCore import QSize
from PySide.QtGui import QBitmap, QImage, QLabel

class TestQBitmap(UsesQApplication):
    def testFromDataMethod(self):
        dataBits = '\x38\x28\x38\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10\xfe\xfe\x7c\x7c\x38\x38\x10\x10'
        bim = QBitmap.fromData(QSize(8, 48), dataBits, QImage.Format_Mono) # missing function

if __name__ == '__main__':
    unittest.main()

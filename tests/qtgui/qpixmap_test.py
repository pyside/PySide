import unittest

from helper import UsesQApplication
from PySide.QtGui import QPixmap
from PySide.QtCore import QVariant

#Only test if is possible create a QPixmap from a QVariant
class QPixmapTest(UsesQApplication):
    def testQVariantConstructor(self):
        pixmap = QPixmap()
        v = QVariant(pixmap)
        pixmap_copy = QPixmap(v)

if __name__ == '__main__':
    unittest.main()


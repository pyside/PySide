import unittest

from helper import UsesQApplication
from PySide.QtGui import *
from PySide.QtCore import *

class QPixmapTest(UsesQApplication):
    def testQVariantConstructor(self):
        pixmap = QPixmap()
        v = QVariant(pixmap)
        pixmap_copy = QPixmap(v)

    def testQSizeConstructor(self):
        pixmap = QPixmap(QSize(10,20))
        self.assert_(pixmap.size().height(), 20)

    def testQStringConstructor(self):
        pixmap = QPixmap(QString("Testing!"))

    def testQVariantConstructor(self):
        v = QVariant(QPixmap())
        pixmap2 = QPixmap(v)
        v = QVariant(QImage())
        pixmap2 = QPixmap(v)

if __name__ == '__main__':
    unittest.main()


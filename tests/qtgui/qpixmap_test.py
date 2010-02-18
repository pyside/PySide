import unittest

from helper import UsesQApplication
from PySide.QtGui import QPixmap
from PySide.QtCore import QVariant, QSize, QString

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

if __name__ == '__main__':
    unittest.main()


import unittest

import os
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

    def testQVariantConstructor2(self):
        v = QVariant(QPixmap())
        pixmap2 = QPixmap(v)
        v = QVariant(QImage())
        pixmap2 = QPixmap(v)

    def testQPixmapLoadFromDataWithQFile(self):
        f = QFile(os.path.join(os.path.dirname(__file__), 'sample.png'))
        self.assert_(f.open(QIODevice.ReadOnly))
        data = f.read(f.size())
        f.close()
        pixmap = QPixmap()
        self.assert_(pixmap.loadFromData(data))

    def testQPixmapLoadFromDataWithPython(self):
        data = open(os.path.join(os.path.dirname(__file__),'sample.png'),'rb').read()
        pixmap = QPixmap()
        self.assert_(pixmap.loadFromData(data))

if __name__ == '__main__':
    unittest.main()


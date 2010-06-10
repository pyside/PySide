import unittest

import os
from helper import UsesQApplication
from PySide.QtGui import *
from PySide.QtCore import *

class QPixmapTest(UsesQApplication):
    def testQVariantConstructor(self):
        obj = QObject()
        pixmap = QPixmap()
        obj.setProperty('foo', pixmap)
        self.assertEqual(type(obj.property('foo')), QPixmap)

    def testQSizeConstructor(self):
        pixmap = QPixmap(QSize(10,20))
        self.assert_(pixmap.size().height(), 20)

    def testQStringConstructor(self):
        pixmap = QPixmap("Testing!")

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


class QPixmapToImage(UsesQApplication):

    def testFilledImage(self):
        '''QPixmap.fill + toImage + image.pixel'''
        pixmap = QPixmap(100, 200)
        pixmap.fill(Qt.red) # Default Qt.white

        self.assertEqual(pixmap.height(), 200)
        self.assertEqual(pixmap.width(), 100)

        image = pixmap.toImage()

        self.assertEqual(image.height(), 200)
        self.assertEqual(image.width(), 100)

        pixel = image.pixel(10,10)
        self.assertEqual(pixel, QColor(Qt.red).rgba())


if __name__ == '__main__':
    unittest.main()


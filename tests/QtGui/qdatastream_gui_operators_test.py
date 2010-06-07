# -*- coding: utf-8 -*-

import unittest
import sys

from PySide.QtCore import QDataStream, QByteArray, QIODevice, Qt
from PySide.QtGui import QPixmap, QColor

from helper import UsesQApplication

class QPixmapQDatastream(UsesQApplication):
    '''QDataStream <<>> QPixmap'''

    def setUp(self):
        super(QPixmapQDatastream, self).setUp()
        self.source_pixmap = QPixmap(100, 100)
        self.source_pixmap.fill(Qt.red)
        self.output_pixmap = QPixmap()
        self.buffer = QByteArray()
        self.read_stream = QDataStream(self.buffer, QIODevice.ReadOnly)
        self.write_stream = QDataStream(self.buffer, QIODevice.WriteOnly)

    def testStream(self):
        self.write_stream << self.source_pixmap

        self.read_stream >> self.output_pixmap

        image = self.output_pixmap.toImage()
        pixel = image.pixel(10,10)
        self.assertEqual(pixel, QColor(Qt.red).rgba())
        self.assertEqual(self.source_pixmap.toImage(), self.output_pixmap.toImage())


if __name__ == '__main__':
    unittest.main()

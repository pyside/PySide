#!/usr/bin/python
import unittest
from sys import getrefcount
from PySide.QtCore import QBuffer
from PySide.QtSvg import QSvgGenerator

class QSvgGeneratorTest(unittest.TestCase):

    def testRefCountOfTOutputDevice(self):
        generator = QSvgGenerator()
        iodevice1 = QBuffer()
        refcount1 = getrefcount(iodevice1)

        generator.setOutputDevice(iodevice1)

        self.assertEqual(generator.outputDevice(), iodevice1)
        self.assertEqual(getrefcount(generator.outputDevice()), refcount1 + 1)

        iodevice2 = QBuffer()
        refcount2 = getrefcount(iodevice2)

        generator.setOutputDevice(iodevice2)

        self.assertEqual(generator.outputDevice(), iodevice2)
        self.assertEqual(getrefcount(generator.outputDevice()), refcount2 + 1)
        self.assertEqual(getrefcount(iodevice1), refcount1)

        del generator

        self.assertEqual(getrefcount(iodevice2), refcount2)

if __name__ == '__main__':
    unittest.main()


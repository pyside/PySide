# -*- coding: utf-8 -*-

'''Test cases for QResource usage'''

import unittest
from helper import adjust_filename
from PySide.QtCore import QFile, QIODevice
import resources_mc

class ResourcesUsage(unittest.TestCase):
    '''Test case for resources usage'''

    def testPhrase(self):
        #Test loading of quote.txt resource
        f = open(adjust_filename('quoteEnUS.txt', __file__), "r")
        orig = f.read()
        f.close()

        f = QFile(':/quote.txt')
        f.open(QIODevice.ReadOnly) #|QIODevice.Text)
        print("Error:", f.errorString())
        copy = f.readAll()
        f.close()
        self.assertEqual(orig, copy)

    def testImage(self):
        #Test loading of sample.png resource
        f = open(adjust_filename('sample.png', __file__), "rb")
        orig = f.read()
        f.close()

        f = QFile(':/sample.png')
        f.open(QIODevice.ReadOnly)
        copy = f.readAll()
        f.close()
        self.assertEqual(len(orig), len(copy))
        self.assertEqual(orig, copy)


if __name__ == '__main__':
    unittest.main()


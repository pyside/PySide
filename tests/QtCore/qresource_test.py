# -*- coding: utf-8 -*-

'''Test cases for QResource usage'''

import unittest
import os
from PySide.QtCore import QFile, QIODevice
import resources_mc

class ResourcesUsage(unittest.TestCase):
    '''Test case for resources usage'''

    def setUp(self):
        f = open(os.path.join(os.path.dirname(__file__), 'quoteEnUS.txt'))
        self.text = f.read()
        f.close()

    def tearDown(self):
        self.text = None

    def testPhrase(self):
        #Test loading of quote.txt resource
        f = QFile(':/quote.txt')
        f.open(QIODevice.ReadOnly|QIODevice.Text)
        content = f.readAll()
        f.close()
        self.assertEqual(self.text, content)

if __name__ == '__main__':
    unittest.main()


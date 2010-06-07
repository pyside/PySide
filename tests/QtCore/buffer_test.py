#!/usr/bin/python

import unittest
from PySide.QtCore import QString

class BufferTest(unittest.TestCase):
    def testQByteArray(self):
        data = buffer("PySide")
        str = QString(data)
        self.assertEqual(data, str)

if __name__ == '__main__':
    unittest.main()

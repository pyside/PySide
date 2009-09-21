#!/usr/bin/python
'''Tests for static methos conflicts with class methods'''

import unittest

from PySide import QtCore

class static_function_test(unittest.TestCase):
    def testMemberQFileExists(self):
        f = QtCore.QFile("/tmp/foo.txt")
        self.assertEqual(f.exists(), False)

    def testStatocQFileExists(self):
	self.assertEqual(QtCore.QFile.fileExists("/tmp/foo.txt"), False)

if __name__ == '__main__':
    unittest.main()


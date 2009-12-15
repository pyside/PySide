#!/usr/bin/python
'''Test cases for QProcess'''

import unittest
import os

from PySide.QtCore import *

class TestQProcess (unittest.TestCase):
    def testStartDetached(self):
        tuple_ = QProcess.startDetached("dir", [], os.getcwd())
        self.assertEquals(tuple, tuple_.__class__)
        (value, pid) = tuple_
        self.assertEquals(bool, value.__class__)
        self.assertEqual(long, pid.__class__)

if __name__ == '__main__':
    unittest.main()

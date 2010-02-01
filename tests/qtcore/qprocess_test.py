#!/usr/bin/python
'''Test cases for QProcess'''

import unittest
import os

from PySide.QtCore import *

class TestQProcess (unittest.TestCase):
    def testStartDetached(self):
        value, pid = QProcess.startDetached("dir", [], os.getcwd())
        self.assert_(isinstance(value, bool))
        self.assert_(isinstance(pid, long))

if __name__ == '__main__':
    unittest.main()

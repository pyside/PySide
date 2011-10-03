#!/usr/bin/python
'''Test cases for QProcess'''

import unittest
import os
import py3kcompat as py3k

from PySide.QtCore import *

class TestQProcess (unittest.TestCase):
    def testStartDetached(self):
        value, pid = QProcess.startDetached("dir", [], os.getcwd())
        self.assertTrue(isinstance(value, bool))
        self.assertTrue(isinstance(pid, py3k.long))

    def testPid(self):
        p = QProcess()
        p.start("dir")
        p.waitForStarted()
        pid = p.pid()
        # We can't test the pid method result because it returns 0 when the
        # process isn't running
        if p.state() == QProcess.Running:
            self.assertNotEqual(pid, 0)
        else:
            print("PROCESS ALREADY DEAD :-/")

if __name__ == '__main__':
    unittest.main()

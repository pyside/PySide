#!/usr/bin/python

import unittest
from PySide import QtCore

class Lock(QtCore.QMutex):
    def tryLock(self,timeoutt=10):
        return QtCore.QMutex.tryLock(self,timeoutt)

class TestBug(unittest.TestCase):

    def testCase(self):
        l = Lock()
        l.tryLock() # this cause a assertion


if __name__ == '__main__':
    unittest.main()

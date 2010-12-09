#!/usr/bin/python

import unittest

from PySide.QtCore import *
from PySide.QtGui import *
from helper import UsesQApplication

class NeverDiesTest(UsesQApplication):

    def testIt(self):
        QPrintDialog()

if __name__ == "__main__":
    unittest.main()

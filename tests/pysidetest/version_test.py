#!/usr/bin/python

import unittest
from PySide import __version_info__, __version__, QtCore

class CheckForVariablesTest(unittest.TestCase):
    def testVesions(self):
        self.assert_(__version_info__ >= (1, 0, 0))
        self.assert_(__version_info__ < (99, 99, 99))
        self.assert_(__version__)

        self.assert_(QtCore.__version_info__ >= (4, 5, 0))
        self.assert_(QtCore.__version__)

if __name__ == '__main__':
    unittest.main()


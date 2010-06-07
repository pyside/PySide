# -*- coding: utf-8 -*-

import unittest

from PySide.QtCore import SIGNAL, SLOT

class SIGNALSLOTTests(unittest.TestCase):
    '''Test the output of SIGNAL and SLOT.'''

    def testSIGNAL(self):
        #SIGNAL function
        a = "foobar"
        self.assertEqual(str(SIGNAL(a)), "2foobar")

    def testSLOT(self):
        #SLOT function
        a = "foobar"
        self.assertEqual(str(SLOT(a)), "1foobar")

if __name__ == '__main__':
    unittest.main()

#!/usr/bin/python
# -*- coding: utf-8 -*-
'''Tests QString using QKeySequence parameter'''

import unittest

from PySide.QtCore import QString
from PySide.QtGui import QKeySequence

class QStringQKeySequenceTest(unittest.TestCase):
    '''Tests QString using QKeySequence parameter'''
    
    def testQStringQKeySequence(self):
        a = QString(QKeySequence("Ctrl+A"))

if __name__ == '__main__':
    unittest.main()


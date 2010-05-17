#!/usr/bin/env python
# -*- coding: utf-8 -*-

import unittest
from PySide.QtCore import QObject, Signal

class BoundAndUnboundSignalsTest(unittest.TestCase):

    def setUp(self):
        self.methods = set(('connect', 'disconnect', 'emit'))

    def tearDown(self):
        del self.methods

    def testUnboundSignal(self):
        self.assertEqual(type(QObject.destroyed), Signal)
        self.assertFalse(self.methods.issubset(dir(QObject.destroyed)))

    def testBoundSignal(self):
        obj = QObject()
        self.assertNotEqual(type(obj.destroyed), Signal)
        self.assert_(self.methods.issubset(dir(obj.destroyed)))

if __name__ == '__main__':
    unittest.main()



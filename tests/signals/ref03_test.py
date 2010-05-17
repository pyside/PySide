#!/usr/bin/env python
# -*- coding: utf-8 -*-

import unittest
from sys import getrefcount
from PySide.QtCore import QObject

class DisconnectSignalsTest(unittest.TestCase):

    def setUp(self):
        self.emitter = QObject()

    def tearDown(self):
        del self.emitter

    def testConnectionRefCount(self):

        def destroyedSlot():
            pass

        self.assertEqual(getrefcount(destroyedSlot), 2)
        self.emitter.destroyed.connect(destroyedSlot)
        self.assertEqual(getrefcount(destroyedSlot), 3)
        self.emitter.destroyed.disconnect(destroyedSlot)
        self.assertEqual(getrefcount(destroyedSlot), 2)

if __name__ == '__main__':
    unittest.main()


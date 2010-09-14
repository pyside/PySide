#!/usr/bin/env python
# -*- coding: utf-8 -*-

import unittest
from PySide.QtCore import QObject, SIGNAL

class MultipleSlots(unittest.TestCase):
    def myCB(self):
        self._count += 1

    def testUnboundSignal(self):
        o = QObject()
        self._count  = 0
        for i in range(200):
            QObject.connect(o, SIGNAL("fire()"), lambda: self.myCB())

        o.emit(SIGNAL("fire()"))
        self.assertEqual(self._count, 200)

if __name__ == '__main__':
    unittest.main()



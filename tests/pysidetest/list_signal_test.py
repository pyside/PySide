# -*- coding: utf-8 -*-

import unittest
from testbinding import TestObject
from PySide.QtCore import QObject

class ListConnectionTest(unittest.TestCase):

    def childrenChanged(self, children):
        self._child = children[0]

    def testConnection(self):
        o = TestObject(0)
        c = QObject()
        c.setObjectName("child")
        self._child = None
        o.childrenChanged.connect(self.childrenChanged)
        o.addChild(c)
        self.assertEquals(self._child.objectName(), "child")

if __name__ == '__main__':
    unittest.main()


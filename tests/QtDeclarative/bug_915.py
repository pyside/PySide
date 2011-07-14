#!/usr/bin/python
# -*- coding: utf-8 -*-
import unittest

from PySide.QtDeclarative import QDeclarativeView, QDeclarativeItem
from helper import TimedQApplication

class TestBug915(TimedQApplication):
    def testReturnPolicy(self):
        view = QDeclarativeView()

        item1 = QDeclarativeItem()
        item1.setObjectName("Item1")
        view.scene().addItem(item1)
        self.assertEqual(item1.objectName(), "Item1") # check if the item still valid

        item2 = QDeclarativeItem()
        item2.setObjectName("Item2")
        item1.scene().addItem(item2)
        item1 = None
        self.assertEqual(item2.objectName(), "Item2") # check if the item still valid

        view = None

if __name__ == '__main__':
    unittest.main()



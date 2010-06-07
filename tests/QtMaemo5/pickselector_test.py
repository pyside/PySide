#!/usr/bin/python
import unittest
from PySide.QtMaemo5 import QMaemo5ListPickSelector, QMaemo5ValueButton

from helper import UsesQApplication

class PickSelectorTest(UsesQApplication):
    def testOwnership(self):
        pickselector = QMaemo5ListPickSelector()
        button = QMaemo5ValueButton("test")
        button.setPickSelector(pickselector)
        del pickselector
        self.assert_(button.pickSelector())

if __name__ == '__main__':
    unittest.main()


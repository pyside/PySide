#!/usr/bin/python
import unittest
from PySide.QtCore import *


class SetPropOnCtorTest(unittest.TestCase):
    def testIt(self):
        obj = QEventTransition(targetStates = [QState()])
        self.assertEqual(len(obj.targetStates()), 1);

if __name__ == '__main__':
    unittest.main()

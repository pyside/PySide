#!/usr/bin/env python

import unittest
from PySide.QtCore import *

class ArgsDontMatch(unittest.TestCase):

    def callback(self, arg1):
        self.ok = True

    def testConnectSignalToSlotWithLessArgs(self):
        self.ok = False
        obj1 = QObject()
        QObject.connect(obj1, SIGNAL('the_signal(int, int, int)'), self.callback)
        obj1.emit(SIGNAL('the_signal(int, int, int)'), 1, 2, 3)

        self.assert_(self.ok)



if __name__ == '__main__':
    unittest.main()

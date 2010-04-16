#!/usr/bin/python
import unittest
from PySide.QtMaemo5 import *
from PySide import QtGui

from helper import UsesQApplication

class QtMamo5Test(UsesQApplication):

    def testObjectCreate(self):
        bar = QMaemo5EditBar()
        self.assert_(isinstance(bar, QMaemo5EditBar))

    def testGui(self):
        getattr(QtGui, 'QAbstractKineticScroller')

if __name__ == '__main__':
    unittest.main()


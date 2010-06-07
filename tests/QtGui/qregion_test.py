import unittest
import sys

from PySide.QtGui import QRegion
from PySide.QtCore import QPoint
from helper import UsesQApplication

class QRegionTest(UsesQApplication):

    def testFunctionUnit(self):
        r = QRegion(0, 0, 10, 10)
        r2 = QRegion(5, 5, 10, 10)
 
        ru = r.united(r2)
        self.assert_(ru.contains(QPoint(0,0)))
        self.assert_(ru.contains(QPoint(5,5)))
        self.assert_(ru.contains(QPoint(10,10)))
        self.assert_(ru.contains(QPoint(14,14)))

if __name__ == '__main__':
    unittest.main()

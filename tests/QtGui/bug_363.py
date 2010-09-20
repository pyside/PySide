''' Test bug 363: http://bugs.openbossa.org/show_bug.cgi?id=363'''

import sys
import unittest
from helper import UsesQApplication
from PySide import QtCore,QtGui

# Check for desktop object lifetime
class BugTest(UsesQApplication):
    def mySlot(self):
        pass

    # test if it is possible to connect with a desktop object after storing that on an auxiliar variable
    def testCase1(self):
        desktop = QtGui.QApplication.desktop()
        desktop.resized[int].connect(self.mySlot)
        self.assert_(True)

    # test if it is possible to connect with a desktop object without storing that on an auxiliar variable
    def testCase2(self):
        QtGui.QApplication.desktop().resized[int].connect(self.mySlot)
        self.assert_(True)

if __name__ == '__main__':
    unittest.main()

''' Test bug 389: http://bugs.openbossa.org/show_bug.cgi?id=389'''

import sys
import unittest
from helper import UsesQApplication
from PySide import QtCore,QtGui

class BugTest(UsesQApplication):
    def testCase(self):
        s = QtGui.QWidget().style()
        i = s.standardIcon(QtGui.QStyle.SP_TitleBarMinButton)
        self.assertEqual(type(i), QtGui.QIcon)

if __name__ == '__main__':
    unittest.main()

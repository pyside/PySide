''' Test bug 512: http://bugs.openbossa.org/show_bug.cgi?id=512'''

import unittest
from helper import UsesQApplication
from PySide.QtCore import *
from PySide.QtGui import *

class BugTest(UsesQApplication):
    def testCase(self):
        w = QWidget(None)
        lbl = QLabel("Hello", w);
        g = QGridLayout()
        g.addWidget(lbl, 0, 0)
        w.setLayout(g)
        w.show()

        t = g.getItemPosition(0)
        self.assertEqual(type(t), tuple)
        self.assertEqual(t, (0,0,1,1))

if __name__ == '__main__':
    unittest.main()

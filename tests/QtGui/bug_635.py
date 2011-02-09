''' Test bug 635: http://bugs.openbossa.org/show_bug.cgi?id=635'''

import unittest
from PySide.QtGui import QApplication, QToolBar, QIcon
import sys

class testQToolBar(unittest.TestCase):
    def callback(self):
        self._called = True

    def testAddAction(self):
        bar = QToolBar()
        self._called = False
        a = bar.addAction("act1", self.callback)
        a.trigger()
        self.assert_(self._called)

    def testAddActionWithIcon(self):
        bar = QToolBar()
        self._called = False
        icon = QIcon()
        a = bar.addAction(icon, "act1", self.callback)
        a.trigger()
        self.assert_(self._called)

if __name__ == '__main__':
    app = QApplication(sys.argv)
    unittest.main()

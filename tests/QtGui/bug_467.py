''' Test bug 367: http://bugs.openbossa.org/show_bug.cgi?id=467'''

import unittest
from helper import UsesQApplication
from PySide.QtGui import QMainWindow, QApplication

class MyWidget(QMainWindow):
    def __init__(self, parent = None):
        QMainWindow.__init__(self, parent)


class BugTest(UsesQApplication):
    def testCase(self):
        w = MyWidget()
        widgets = QApplication.allWidgets()
        self.assert_(w in widgets)

if __name__ == '__main__':
    unittest.main()

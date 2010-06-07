
'''Tests for calling methods further than the direct parent'''

import unittest

from PySide.QtGui import QPushButton, QWidget

from helper import UsesQApplication

class Dummy(QPushButton):

    def show(self):
        QWidget.show(self)
        self.called = True

class GrandParentMethod(UsesQApplication):
    def testMethod(self):
        obj = Dummy()
        obj.show()
        self.assert_(obj.called)

if __name__ == '__main__':
    unittest.main()

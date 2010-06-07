
'''Tests for QMenuBar.addAction(identifier, callback) calls'''

import unittest

from PySide.QtCore import SLOT
from PySide.QtGui import QMenuBar, QAction, QPushButton

from helper import UsesQApplication


class AddActionTest(UsesQApplication):
    '''QMenuBar addAction'''

    def tearDown(self):
        try:
            del self.called
        except AttributeError:
            pass
        super(AddActionTest, self).tearDown()

    def _callback(self):
        self.called = True

    def testBasic(self):
        '''QMenuBar.addAction(id, callback)'''
        menubar = QMenuBar()
        action = menubar.addAction("Accounts", self._callback)
        action.activate(QAction.Trigger)
        self.assert_(self.called)

    def testWithCppSlot(self):
        '''QMenuBar.addAction(id, object, slot)'''
        menubar = QMenuBar()
        widget = QPushButton()
        widget.setCheckable(True)
        widget.setChecked(False)
        action = menubar.addAction("Accounts", widget, SLOT("toggle()"))
        action.activate(QAction.Trigger)
        self.assert_(widget.isChecked())

if __name__ == '__main__':
    unittest.main()


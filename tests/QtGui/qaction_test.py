import unittest

from PySide.QtGui import QAction, QWidget
from helper import UsesQApplication

class QPainterDrawText(UsesQApplication):

    def _cb(self):
        self._called = True

    def testSignal(self):
        o = QWidget()
        act = QAction(o)
        self._called = False
        act.triggered.connect(self._cb)
        act.trigger()
        self.assert_(self._called)

    def testNewCtor(self):
        o = QWidget()
        self._called = False
        myAction = QAction("&Quit", o, triggered=self._cb)
        myAction.trigger()
        self.assert_(self._called)


class SetShortcutTest(UsesQApplication):

    def testSetShortcut(self):
        # Somehow an exception was leaking from the constructor
        # and appearing in setShortcut.
        o = QWidget()
        action = QAction('aaaa', o)
        shortcut = 'Ctrl+N'
        action.setShortcut(shortcut)
        s2 = action.shortcut()
        self.assertEqual(s2, shortcut)

if __name__ == '__main__':
    unittest.main()


from PySide.QtGui import QMenu, QWidget, QMenuBar, QToolBar
import weakref

import unittest
from helper import UsesQApplication


class TestQActionLifeCycle(UsesQApplication):
    def actionDestroyed(self, act):
        self._actionDestroyed = True

    def testMenu(self):
        self._actionDestroyed = False
        w = QWidget()
        menu = QMenu(w)
        act = menu.addAction("MENU")
        _ref = weakref.ref(act, self.actionDestroyed)
        act = None
        self.assertFalse(self._actionDestroyed)
        menu.clear()
        self.assertTrue(self._actionDestroyed)

    def testMenuBar(self):
        self._actionDestroyed = False
        w = QWidget()
        menuBar = QMenuBar(w)
        act = menuBar.addAction("MENU")
        _ref = weakref.ref(act, self.actionDestroyed)
        act = None
        self.assertFalse(self._actionDestroyed)
        menuBar.clear()
        self.assertTrue(self._actionDestroyed)

    def testToolBar(self):
        self._actionDestroyed = False
        w = QWidget()
        toolBar = QToolBar(w)
        act = toolBar.addAction("MENU")
        _ref = weakref.ref(act, self.actionDestroyed)
        act = None
        self.assertFalse(self._actionDestroyed)
        toolBar.clear()
        self.assertTrue(self._actionDestroyed)

if __name__ == "__main__":
    unittest.main()

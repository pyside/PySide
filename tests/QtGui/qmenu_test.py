
import unittest

from PySide.QtGui import QMenu, QKeySequence, QIcon
from PySide.QtCore import SLOT

from helper import UsesQApplication

class QMenuAddAction(UsesQApplication):

    def setUp(self):
        super(QMenuAddAction, self).setUp()
        self.menu = QMenu()

    def tearDown(self):
        del self.menu
        super(QMenuAddAction, self).tearDown()

    def testAddActionWithoutKeySequenceCallable(self):
        # bug #280
        action = self.menu.addAction(self.app.tr('aaa'), lambda : 1)

    def testAddActionKeySequenceCallable(self):
        # bug #228
        action = self.menu.addAction(self.app.tr('aaa'), lambda : 1,
                                    QKeySequence(self.app.tr('Ctrl+O')))

    def testAddActionKeySequenceSlot(self):
        action = self.menu.addAction('Quit', self.app, SLOT('quit()'),
                                    QKeySequence('Ctrl+O'))

class QMenuAddActionWithIcon(UsesQApplication):

    def setUp(self):
        super(QMenuAddActionWithIcon, self).setUp()
        self.menu = QMenu()
        self.icon = QIcon()

    def tearDown(self):
        del self.menu
        del self.icon
        super(QMenuAddActionWithIcon, self).tearDown()

    def testAddActionWithoutKeySequenceCallable(self):
        # bug #280
        action = self.menu.addAction(self.icon, self.app.tr('aaa'), lambda : 1)

    def testAddActionKeySequenceCallable(self):
        # bug #228
        action = self.menu.addAction(self.icon, self.app.tr('aaa'), lambda : 1,
                                    QKeySequence(self.app.tr('Ctrl+O')))

    def testAddActionKeySequenceSlot(self):
        action = self.menu.addAction(self.icon, 'Quit', self.app, SLOT('quit()'),
                                    QKeySequence('Ctrl+O'))

if __name__ == '__main__':
    unittest.main()

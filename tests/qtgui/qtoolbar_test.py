
'''Test cases for QToolbar'''

import unittest

from PySide.QtGui import QToolBar, QMainWindow, QAction

from helper import UsesQApplication

class AddActionText(UsesQApplication):
    '''Test case for calling QToolbar.addAction passing a text'''

    def setUp(self):
        #Acquire resources
        super(AddActionText, self).setUp()
        self.window = QMainWindow()
        self.toolbar = QToolBar()
        self.window.addToolBar(self.toolbar)

    def tearDown(self):
        #Release resources
        super(AddActionText, self).tearDown()
        del self.toolbar
        del self.window

    def testText(self):
        #QToolBar.addAction(text) - add a QToolButton
        self.toolbar.addAction('aaaa')
        self.assertEqual(len(self.toolbar.actions()), 1)
        action = self.toolbar.actions()[0]
        self.assert_(isinstance(action, QAction))
        self.assertEqual(action.text(), 'aaaa')

if __name__ == '__main__':
    unittest.main()

#!/usr/bin/python
# -*- coding: utf-8 -*-
'''Tests conversions of QString to and from QKeySequence.'''

import unittest
from helper import UsesQApplication

from PySide.QtCore import QString
from PySide.QtGui import QKeySequence, QAction

class QStringQKeySequenceTest(UsesQApplication):
    '''Tests conversions of QString to and from QKeySequence.'''

    def testQStringFromQKeySequence(self):
        '''Creates a QString from a QKeySequence.'''
        keyseq = 'Ctrl+A'
        a = QString(QKeySequence(keyseq))
        self.assertEqual(a, keyseq)

    def testQStringAsQKeySequence(self):
        '''Passes a QString to an argument expecting a QKeySequence.'''
        keyseq = QString('Ctrl+A')
        action = QAction(None)
        action.setShortcut(keyseq)
        shortcut = action.shortcut()
        self.assert_(isinstance(shortcut, QKeySequence))
        self.assertEqual(shortcut.toString(), keyseq)

    def testPythonStringAsQKeySequence(self):
        '''Passes a Python string to an argument expecting a QKeySequence.'''
        keyseq = 'Ctrl+A'
        action = QAction(None)
        action.setShortcut(keyseq)
        shortcut = action.shortcut()
        self.assert_(isinstance(shortcut, QKeySequence))
        self.assertEqual(shortcut.toString(), keyseq)

if __name__ == '__main__':
    unittest.main()


#!/usr/bin/python
# -*- coding: utf-8 -*-
'''Tests conversions of QString to and from QKeySequence.'''

import unittest
import py3kcompat as py3k
from helper import UsesQApplication

from PySide.QtGui import QKeySequence, QAction

class QStringQKeySequenceTest(UsesQApplication):
    '''Tests conversions of QString to and from QKeySequence.'''

    def testQStringFromQKeySequence(self):
        '''Creates a QString from a QKeySequence.'''
        keyseq = 'Ctrl+A'
        a = QKeySequence(keyseq)
        self.assertEqual(a, keyseq)

    def testPythonStringAsQKeySequence(self):
        '''Passes a Python string to an argument expecting a QKeySequence.'''
        keyseq = py3k.unicode_('Ctrl+A')
        action = QAction(None)
        action.setShortcut(keyseq)
        shortcut = action.shortcut()
        self.assert_(isinstance(shortcut, QKeySequence))
        self.assertEqual(shortcut.toString(), keyseq)

if __name__ == '__main__':
    unittest.main()


'''Test cases for QTextEdit and ownership problems.'''

import unittest
from sys import getrefcount
from PySide.QtGui import QTextEdit

from helper import UsesQApplication

class DontTouchReference(UsesQApplication):
    '''Check if the QTextTable returned by QTextCursor.insertTable() is not
    referenced by the QTextCursor that returns it.'''

    def setUp(self):
        super(DontTouchReference, self).setUp()
        self.editor = QTextEdit()
        self.cursor = self.editor.textCursor()
        self.table = self.cursor.insertTable(1, 1)

    def testQTextTable(self):
        # methods which return QTextTable should not increment its reference
        self.assertEqual(getrefcount(self.table), 2)
        f = self.cursor.currentFrame()
        del f
        self.assertEqual(getrefcount(self.table), 2)
        # destroying the cursor should not raise any "RuntimeError: internal
        # C++ object already deleted." when accessing the QTextTable
        del self.cursor
        self.assertEqual(getrefcount(self.table), 2)
        cell = self.table.cellAt(0, 0)

if __name__ == "__main__":
    unittest.main()

import unittest
import sys
import weakref

from helper import UsesQApplication

from PySide.QtGui import QTextBlockUserData, QTextEdit, QTextCursor

class TestUserData(QTextBlockUserData):
    def __init__(self, data):
        super(TestUserData, self).__init__()
        self.data = data

class TestUserDataRefCount(UsesQApplication):
    def testRefcount(self):
        textedit = QTextEdit()
        textedit.setReadOnly(True)
        doc = textedit.document()
        cursor = QTextCursor(doc)
        cursor.insertText("PySide Rocks")
        ud = TestUserData({"Life": 42})
        self.assertEqual(sys.getrefcount(ud), 2)
        cursor.block().setUserData(ud)
        self.assertEqual(sys.getrefcount(ud), 3)
        ud2 = cursor.block().userData()
        self.assertEqual(sys.getrefcount(ud), 4)
        self.udata = weakref.ref(ud, None)
        del ud, ud2
        self.assertEqual(sys.getrefcount(self.udata()), 2)

if __name__ == '__main__':
    unittest.main()

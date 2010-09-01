import unittest
import colorsys

from PySide.QtCore import *
from PySide.QtGui import *
from helper import UsesQApplication

class Foo(QPyTextObject):
    called = False

    def intrinsicSize(self, doc, posInDocument, format):
        Foo.called = True
        return QSizeF(10, 10)

    def drawObject(self, painter, rect, doc, posInDocument, format):
        pass

class QAbstractTextDocumentLayoutTest(UsesQApplication):

    objectType = QTextFormat.UserObject + 1

    def foo(self):
        fmt = QTextCharFormat()
        fmt.setObjectType(QAbstractTextDocumentLayoutTest.objectType)

        cursor = self.textEdit.textCursor()
        cursor.insertText(unichr(0xfffc), fmt)
        self.textEdit.setTextCursor(cursor)
        self.textEdit.close()

    def testIt(self):

        self.textEdit = QTextEdit()
        self.textEdit.show()

        interface = Foo()
        self.textEdit.document().documentLayout().registerHandler(QAbstractTextDocumentLayoutTest.objectType, interface)

        QTimer.singleShot(0, self.foo)
        self.app.exec_()

        self.assertTrue(Foo.called)

if __name__ == "__main__":
    unittest.main()


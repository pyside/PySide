""" Unittest for bug #575 """
""" http://bugs.openbossa.org/show_bug.cgi?id=575 """

from PySide.QtGui import QApplication, QPlainTextEdit, QTextEdit
import sys
import unittest

class Bug575(unittest.TestCase):
    def testPropertyValues(self):
        app = QApplication(sys.argv)
        textEdit = QPlainTextEdit()
        textEdit.insertPlainText("PySide INdT")
        selection = QTextEdit.ExtraSelection()
        selection.cursor = textEdit.textCursor()
        selection.cursor.setPosition(2)
        self.assertEqual(selection.cursor.position(), 2)

if __name__ == '__main__':
    unittest.main()


''' Test bug 662: http://bugs.openbossa.org/show_bug.cgi?id=662'''

import unittest
from PySide.QtGui import QTextEdit, QApplication, QTextCharFormat
import sys

class testQTextBlock(unittest.TestCase):
    def tesIterator(self):
        edit = QTextEdit()
        cursor = edit.textCursor()
        fmt = QTextCharFormat()
        frags = []
        for i in range(10):
            fmt.setFontPointSize(i+10)
            frags.append("block%d"%i)
            cursor.insertText(frags[i], fmt)

        doc = edit.document()
        block = doc.begin()

        index = 0
        for i in block:
            self.assertEqual(i.fragment().text(), frags[index])
            index += 1

if __name__ == '__main__':
    app = QApplication(sys.argv)
    unittest.main()


import unittest

from PySide.QtGui import QTextDocument, QTextCursor

class QTextDocumentTest(unittest.TestCase):

    def testUndoRedo(self):
        text = 'foobar'
        doc = QTextDocument(text)

        self.assertFalse(doc.isRedoAvailable())
        self.assertTrue(doc.isUndoAvailable())
        self.assertEqual(doc.toPlainText(), text)

        cursor = QTextCursor(doc)
        doc.undo(cursor)

        self.assertTrue(doc.isRedoAvailable())
        self.assertFalse(doc.isUndoAvailable())
        self.assertEqual(doc.toPlainText(), '')

        doc.redo(cursor)

        self.assertFalse(doc.isRedoAvailable())
        self.assertTrue(doc.isUndoAvailable())
        self.assertEqual(doc.toPlainText(), text)

if __name__ == '__main__':
    unittest.main()


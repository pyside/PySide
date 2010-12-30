import unittest
from PySide.QtGui import *

class TestBug546(unittest.TestCase):

    """Test to check a crash at exit"""
    def testIt(self):
        app = QApplication([])
        textEdit = QPlainTextEdit()
        completer = QCompleter(("foo", "bar"), textEdit)
        completer.setWidget(textEdit)

if __name__=='__main__':
    unittest.main()

import unittest
from PySide.QtGui import *
from PySide.QtWebKit import *

class TestBug803 (unittest.TestCase):

    def testIt(self):
        app = QApplication([])
        page = QWebPage()
        frame = page.mainFrame()
        frame.setHtml("<html><head></head><body><p>1</p><p>2</p></body></html>")
        elems = frame.findAllElements("p")
        self.assertEqual(len(elems), 2)
        self.assertEqual(elems[0].toPlainText(), "1")
        self.assertEqual(elems[1].toPlainText(), "2")

if __name__ == "__main__":
    unittest.main()

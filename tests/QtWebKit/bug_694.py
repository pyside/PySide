import sys
import unittest
from PySide.QtCore import *
from PySide.QtGui import *
from PySide.QtWebKit import *

class ErrorPage (QWebPage):

    def __init__(self):
        QWebPage.__init__(self)
        self.rcv_extension = None
        self.rcv_url = None
        self.rcv_url_copy = None
        self.rcv_option_type = None
        self.rcv_output_type = None


    def supportsExtension(self, extension):
        return extension == QWebPage.ErrorPageExtension

    def extension(self, extension, option, output):
        self.rcv_extension = extension
        self.rcv_url = option.url
        self.rcv_url_copy = QUrl(option.url)
        self.rcv_option_type = type(option)
        self.rcv_output_type = type(output)
        return True

class TestWebPageExtension(unittest.TestCase):
    def testIt(self):
        app = QApplication([])
        ep = ErrorPage()
        view = QWebView()
        view.setPage(ep)
        view.load("foo://bar") # Some malformmed url
        view.show()

        # If the timeout is 0 the webpage isn't even loaded on Qt4.6-i386, so we use 100 :-)
        QTimer.singleShot(100, app.quit)
        app.exec_()

        self.assertEqual(ep.rcv_extension, QWebPage.ErrorPageExtension)
        self.assertRaises(RuntimeError, ep.rcv_url.__str__)

        self.assertEqual(ep.rcv_url_copy, "foo://bar")
        self.assertEqual(ep.rcv_option_type, QWebPage.ErrorPageExtensionOption)
        self.assertEqual(ep.rcv_output_type, QWebPage.ErrorPageExtensionReturn)

if __name__ == '__main__':
    unittest.main()

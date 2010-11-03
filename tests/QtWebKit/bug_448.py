
'''Test cases for bug: http://bugs.openbossa.org/show_bug.cgi?id=448'''

import unittest
import sys

from PySide.QtGui import QApplication
from PySide.QtWebKit import QWebView

class Bug448(unittest.TestCase):
    def onError(self, erros):
        pass

    def testReturnOwnership(self):
        app = QApplication(sys.argv)
        webview = QWebView()
        webview.page().networkAccessManager().sslErrors.connect(self.onError)

if __name__ == '__main__':
    unittest.main()

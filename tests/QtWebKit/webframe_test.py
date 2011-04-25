import unittest
import sys

from PySide.QtCore import QObject, SIGNAL, QUrl
from PySide.QtWebKit import *
from PySide.QtNetwork import QNetworkRequest

from helper import adjust_filename, UsesQApplication



class TestWebFrame(UsesQApplication):
    def load_finished(self, ok):
        self.assert_(ok)
        page = self.view.page()
        self.assert_(page)
        frame = page.mainFrame()
        self.assert_(frame)
        meta = frame.metaData()
        self.assertEqual(meta['description'], ['PySide Test METADATA.'])
        self.app.quit()

    def testMetaData(self):
        self.view = QWebView()
        QObject.connect(self.view, SIGNAL('loadFinished(bool)'),
                        self.load_finished)
        url = QUrl.fromLocalFile(adjust_filename('fox.html', __file__))
        self.view.setUrl(url)
        self.app.exec_()


if __name__ == '__main__':
    unittest.main()


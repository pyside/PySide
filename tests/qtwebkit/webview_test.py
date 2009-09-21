
'''Test cases for QWebView'''

import unittest

from PySide.QtCore import QObject, SIGNAL, QUrl
from PySide.QtWebKit import QWebView

from helper import adjust_filename, TimedQApplication


class TestLoadFinished(TimedQApplication):
    '''Test case for signal QWebView.loadFinished(bool)'''

    def setUp(self):
        #Acquire resources
        TimedQApplication.setUp(self, timeout=250)
        self.view = QWebView()
        QObject.connect(self.view, SIGNAL('loadFinished(bool)'),
                        self.load_finished)
        self.called = False

    def tearDown(self):
        #Release resources
        del self.view
        self.called = False
        TimedQApplication.tearDown(self)

    def testLoadFinishedFromFile(self):
        url = QUrl.fromLocalFile(adjust_filename('fox.html', __file__))
        self.view.setUrl(url)
        self.app.exec_()

        self.assert_(self.called)

    def testLoadFinishedFromUrl(self):
        url = QUrl('http://www.python.org')
        self.view.setUrl(url)
        self.app.exec_()

    def load_finished(self, ok):
        #Callback to check if load was successful
        self.app.quit()
        if ok:
            self.called = True

if __name__ == '__main__':
    unittest.main()

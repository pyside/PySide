
'''Test cases for QWebView'''

import unittest
import py3kcompat as py3k
import sys

from PySide.QtCore import QObject, SIGNAL, QUrl
from PySide.QtWebKit import QWebPage, QWebView
from PySide.QtNetwork import QNetworkRequest

from helper import adjust_filename, TimedQApplication


class testWebPage(QWebPage):
    def sayMyName(self):
        return 'testWebPage'

class TestLoadFinished(TimedQApplication):
    '''Test case for signal QWebView.loadFinished(bool)'''

    def setUp(self):
        #Acquire resources
        TimedQApplication.setUp(self, timeout=1000)
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

    def testSetPageAndGetPage(self):
        twp = testWebPage()
        self.view.setPage(twp)
        del twp
        p = self.view.page()
        self.assertEqual(p.sayMyName(), 'testWebPage')

        # Setting the same webpage should not incref the python obj
        refCount = sys.getrefcount(p)
        self.view.setPage(p)
        self.assertEquals(sys.getrefcount(p), refCount)

        # Changing the webpage obj should decref the old one
        twp2 = testWebPage()
        self.view.setPage(twp2)
        self.assertEquals(sys.getrefcount(p), refCount - 1)

    def load_finished(self, ok):
        #Callback to check if load was successful
        self.app.quit()
        if ok:
            self.called = True

if __name__ == '__main__':
    unittest.main()

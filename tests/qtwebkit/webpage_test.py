
'''Test cases for QWebPage'''

import unittest

from PySide.QtCore import QObject, SIGNAL, QUrl
from PySide.QtWebKit import QWebPage
from PySide.QtNetwork import QNetworkAccessManager

from helper import adjust_filename, TimedQApplication

#Define a global timeout because TimedQApplication uses a singleton!
#Use a value big enough to run all the tests.
TIMEOUT = 1000

class TestFindText(TimedQApplication):
    '''Test cases for finding text'''

    def setUp(self):
        TimedQApplication.setUp(self, timeout=TIMEOUT)
        self.page = QWebPage()
        QObject.connect(self.page, SIGNAL('loadFinished(bool)'),
                        self.load_finished)
        self.called = False

    def tearDown(self):
        #Release resources
        del self.page
        self.called = False
        TimedQApplication.tearDown(self)

    def testFindSelectText(self):
        url = QUrl.fromLocalFile(adjust_filename('fox.html', __file__))
        self.page.mainFrame().load(url)
        self.app.exec_()
        self.assert_(self.called)

    def load_finished(self, ok):
        #Callback to check if load was successful
        if ok:
            self.called = True
            self.assert_(self.page.findText('fox'))
            self.assertEqual(self.page.selectedText(), 'fox')
        self.app.quit()

class SetNetworkAccessManagerCase(TimedQApplication):

    def setUp(self):
        TimedQApplication.setUp(self, timeout=TIMEOUT)

    def testSetNetworkAccessManager(self):
        page = QWebPage()
        manager = QNetworkAccessManager()
        page.setNetworkAccessManager(manager)

    def testNetWorkAccessManager(self):
        page = QWebPage()
        a = page.networkAccessManager()

if __name__ == '__main__':
    unittest.main()

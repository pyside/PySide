
'''Test cases for QHttp'''

import unittest

from PySide.QtCore import *
from PySide.QtNetwork import *

from helper import UsesQCoreApplication
from httpd import TestServer

class AccessManagerCase(UsesQCoreApplication):

    def setUp(self):
        super(AccessManagerCase, self).setUp()
        self.httpd = TestServer()
        self.httpd.start()
        self.called = False

    def tearDown(self):
        super(AccessManagerCase, self).tearDown()
        if self.httpd:
            self.httpd.shutdown()
            self.httpd = None

    def goAway(self):
        self.httpd.shutdown()
        self.app.quit()
        self.httpd = None

    def slot_replyFinished(self, reply):
        self.assertEqual(type(reply), QNetworkReply)
        self.called = True
        self.goAway()

    def testNetworkRequest(self):
        manager = QNetworkAccessManager()
        manager.finished.connect(self.slot_replyFinished)
        manager.get(QNetworkRequest(QUrl("http://127.0.0.1:%s" % self.httpd.port())))
        self.app.exec_()
        self.assert_(self.called)

if __name__ == '__main__':
    unittest.main()

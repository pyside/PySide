
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
        self.httpd.shutdown()

    def slot_replyFinished(self, reply):
        self.assertEqual(type(reply), QNetworkReply)
        self.called = True
        self.app.quit()

    def testNetworkRequest(self):
        manager = QNetworkAccessManager()
        manager.finished.connect(self.slot_replyFinished)
        manager.get(QNetworkRequest(QUrl("http://localhost:%s" % self.httpd.port())))
        self.app.exec_()
        self.assert_(self.called)
        self.httpd.shutdown()

if __name__ == '__main__':
    unittest.main()

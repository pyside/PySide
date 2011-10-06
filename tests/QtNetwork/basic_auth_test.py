import unittest

from PySide.QtCore import *
from PySide.QtNetwork import *

from helper import UsesQCoreApplication
from httpd import TestServer

class testAuthenticationSignal(UsesQCoreApplication):

    def setUp(self):
        super(testAuthenticationSignal, self).setUp()
        self.httpd = TestServer(secure=True)
        self.httpd.start()
        self._resultOk = False

    def tearDown(self):
        if self.httpd:
            self.httpd.shutdown()
            del self.httpd
        super(testAuthenticationSignal, self).tearDown()

    def goAway(self):
        self.httpd.shutdown()
        self.app.quit()
        self.httpd = None

    def onAuthRequest(self, hostname, port, auth):
        self.assertTrue(isinstance(auth, QAuthenticator))
        self._resultOk = True
        self.goAway()

    def testwaitSignal(self):
        http = QHttp('127.0.0.1', self.httpd.port())
        http.connect(SIGNAL("authenticationRequired(const QString&, quint16, QAuthenticator*)"), self.onAuthRequest)
        path = QUrl.toPercentEncoding("/index.html", "!$&'()*+,;=:@/")
        data = http.get(str(path))
        self.app.exec_()
        self.assertTrue(self._resultOk)

    def testwaitSignal2(self):
        http = QHttp('127.0.0.1', self.httpd.port())
        # Using new signal slot syntax causes a segfault
        http.authenticationRequired.connect(self.onAuthRequest)
        path = QUrl.toPercentEncoding("/index.html", "!$&'()*+,;=:@/")
        data = http.get(str(path))
        self.app.exec_()
        self.assertTrue(self._resultOk)

if __name__ == '__main__':
    unittest.main()

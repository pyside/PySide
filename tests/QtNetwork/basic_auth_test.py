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
        self.httpd.shutdown()
        del self.httpd
        super(testAuthenticationSignal, self).tearDown()

    def onAuthRequest(self, hostname, port, auth):
        self.assert_(isinstance(auth, QAuthenticator))
        self._resultOk = True
        self.app.quit()


    def testwaitSignal(self):
        http = QHttp()
        http.setHost("localhost", self.httpd.port())
        http.connect(SIGNAL("authenticationRequired(const QString&, quint16, QAuthenticator*)"), self.onAuthRequest)
        path = QUrl.toPercentEncoding("/index.html", "!$&'()*+,;=:@/")
        data = http.get(str(path))
        self.app.exec_()
        self.assert_(self._resultOk)

    def testwaitSignal2(self):
        http = QHttp()
        http.setHost("localhost", self.httpd.port())
        # Using new signal slot syntax causes a segfault
        http.authenticationRequired.connect(self.onAuthRequest)
        path = QUrl.toPercentEncoding("/index.html", "!$&'()*+,;=:@/")
        data = http.get(str(path))
        self.app.exec_()
        self.assert_(self._resultOk)

if __name__ == '__main__':
    unittest.main()


'''Test cases for QHttp'''

import unittest

from PySide.QtCore import *
from PySide.QtNetwork import *

from helper import UsesQApplication

"""
class HttpSignalsCase(UsesQApplication):
    '''Test case for launching QHttp signals'''

    def setUp(self):
        super(HttpSignalsCase, self).setUp()

        self.http = QHttp()
        self.url = QUrl('http://www.google.com')
        self.timer = QTimer.singleShot(250, self.app.quit)

    def tearDown(self):
        del self.http
        super(HttpSignalsCase, self).tearDown()

    def callback(self, ident):
        self.called = True

    def testDefaultArgs(self):
        #QHttp signal requestStarted signal
        # @bug 114
        QObject.connect(self.http, SIGNAL('requestStarted(int)'), self.callback)
        self.http.get(self.url.path())

        self.app.exec_()
        self.assert_(self.called)

class testHttp(UsesQApplication):
    def testRead(self):
        header = QHttpRequestHeader("GET", QString(QUrl.toPercentEncoding("/index.html")))
        header.setValue("Host", "qtsoftware.com");
        http = QHttp()
        http.setHost("qtsoftware.com")
        http.request(header)
        data = http.read(100)
"""

class testAuthenticationSignal(UsesQApplication):
    def onAuthRequest(self, hostname, port, auth):
        self.assert_(isinstance(auth, QAuthenticator))
        print auth.realm()
        self._resultOk = True
        self.app.exit()

    def testwaitSignal(self):
        self._resultOk = False
        http = QHttp()
        http.setHost("projects.maemo.org", QHttp.ConnectionModeHttps, 0)
        http.connect(SIGNAL("authenticationRequired(const QString&, quint16, QAuthenticator*)"), self.onAuthRequest)
        path = QUrl.toPercentEncoding("/index.html", "!$&'()*+,;=:@/")
        print http.get(path)
        self.app.exec_()
        self.assert_(self._resultOk)


if __name__ == '__main__':
    unittest.main()

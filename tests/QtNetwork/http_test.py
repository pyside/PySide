
'''Test cases for QHttp'''

import unittest

from PySide.QtCore import *
from PySide.QtNetwork import *

from helper import UsesQApplication
from httpd import TestServer

class HttpSignalsCase(UsesQApplication):
    '''Test case for launching QHttp signals'''

    def setUp(self):
        super(HttpSignalsCase, self).setUp()
        self.http = QHttp()
        self.httpd = TestServer()
        self.httpd.start()
        self.url = QUrl('localhost:' + str(self.httpd.port()))
        self.called = False

    def tearDown(self):
        self.httpd.shutdown()
        del self.http
        super(HttpSignalsCase, self).tearDown()

    def callback(self, ident):
        self.called = True
        self.app.quit()

    def testDefaultArgs(self):
        #QHttp signal requestStarted signal
        # @bug 114
        QObject.connect(self.http, SIGNAL('requestStarted(int)'), self.callback)
        self.http.get(self.url.path())

        self.app.exec_()
        self.assert_(self.called)

if __name__ == '__main__':
    unittest.main()

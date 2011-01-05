
'''Test cases for QHttp'''

import unittest

from PySide.QtCore import *
from PySide.QtNetwork import *

from helper import UsesQCoreApplication
from httpd import TestServer

class HttpSignalsCase(UsesQCoreApplication):
    '''Test case for launching QHttp signals'''

    def setUp(self):
        super(HttpSignalsCase, self).setUp()
        self.httpd = TestServer()
        self.httpd.start()
        self.http = QHttp("127.0.0.1" , self.httpd.port())
        self.called = False

    def tearDown(self):
        if self.httpd:
            self.httpd.shutdown()
            del self.httpd
        self.http = None
        self.httpd = None
        super(HttpSignalsCase, self).tearDown()

    def goAway(self):
        self.httpd.shutdown()
        self.app.quit()

    def callback(self, ident):
        self.called = True
        self.goAway()

    def testDefaultArgs(self):
        #QHttp signal requestStarted signal
        # @bug 114
        self.http.requestStarted.connect(self.callback)
        self.http.get("index.html")
        self.app.exec_()
        self.assert_(self.called)

if __name__ == '__main__':
    unittest.main()

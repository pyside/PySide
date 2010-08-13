
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
        self.http = QHttp('localhost' , self.httpd.port())
        self.called = False

    def tearDown(self):
        self.httpd.shutdown()
        self.http = None
        self.httpd = None
        super(HttpSignalsCase, self).tearDown()

    def callback(self, ident):
        self.called = True
        self.app.quit()

    def testDefaultArgs(self):
        #QHttp signal requestStarted signal
        # @bug 114
        self.http.requestStarted.connect(self.callback)
        self.http.get("index.html")
        self.app.exec_()
        self.assert_(self.called)

if __name__ == '__main__':
    unittest.main()


'''Test cases for QHttp'''

import unittest

from PySide.QtCore import *
from PySide.QtNetwork import *

from helper import UsesQApplication

class AccessManagerCase(UsesQApplication):
    def slot_replyFinished(self, reply):
        self.assertEqual(type(reply), QNetworkReply)
        self.app.quit()

    def testNetworkRequest(self):
        manager = QNetworkAccessManager()
        manager.finished.connect(self.slot_replyFinished)
        manager.get(QNetworkRequest(QUrl("http://qt.nokia.com")))
        self.app.exec_()

if __name__ == '__main__':
    unittest.main()

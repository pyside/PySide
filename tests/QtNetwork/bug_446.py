import unittest

from PySide.QtCore import *
from PySide.QtNetwork import *

from helper import UsesQCoreApplication

class HttpSignalsCase(UsesQCoreApplication):
    '''Test case for launching QHttp signals'''
    DATA = "PySide rocks"

    def onError(self):
        self.assert_(False)

    def onNewConnection(self):
        self.serverConnection = self.server.nextPendingConnection()
        self.serverConnection.error.connect(self.onError)
        self.serverConnection.write(HttpSignalsCase.DATA)
        self.server.close()

    def onReadReady(self):
        data = self.client.read(100)
        self.assertEqual(data.size(), len(HttpSignalsCase.DATA))
        self.assertEqual(data, HttpSignalsCase.DATA)
        self.done()

    def onClientConnect(self):
        self.client.readyRead.connect(self.onReadReady)

    def initServer(self):
        self.server = QTcpServer()
        self.server.newConnection.connect(self.onNewConnection)
        self.assert_(self.server.listen())
        self.client = QTcpSocket()
        self.client.connected.connect(self.onClientConnect)
        self.client.connectToHost(QHostAddress(QHostAddress.LocalHost), self.server.serverPort())

    def done(self):
        self.serverConnection.close()
        self.client.close()
        self.app.quit()

    def testRun(self):
        self.initServer()
        self.app.exec_()

if __name__ == '__main__':
    unittest.main()

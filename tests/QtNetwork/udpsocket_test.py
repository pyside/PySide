
'''Test cases for QUdpSocket'''

import unittest

from PySide.QtCore import QUrl, QObject, SIGNAL, QCoreApplication, QTimer
from PySide.QtNetwork import QUdpSocket, QHostAddress

class HttpSignalsCase(unittest.TestCase):
    '''Test case for bug #124 - readDatagram signature

    QUdpSocket.readDatagram must return a tuple with the datagram, host and
    port, while receiving only the max payload size.'''

    def setUp(self):
        #Acquire resources
        self.called = False
        self.app = QCoreApplication([])

        self.socket = QUdpSocket()

        self.server = QUdpSocket()
        self.server.bind(QHostAddress(QHostAddress.LocalHost), 45454)

    def tearDown(self):
        #Release resources
        del self.socket
        del self.server
        del self.app

    def sendPackage(self):
        addr = QHostAddress(QHostAddress.LocalHost)
        self.socket.writeDatagram('datagram', addr, 45454)

    def callback(self):
        while self.server.hasPendingDatagrams():
            datagram, host, port = self.server.readDatagram(self.server.pendingDatagramSize())
            self.called = True
            self.app.quit()

    def testDefaultArgs(self):
        #QUdpSocket.readDatagram pythonic return
        # @bug 124
        QObject.connect(self.server, SIGNAL('readyRead()'), self.callback)
        self.sendPackage()
        self.app.exec_()

        self.assert_(self.called)

if __name__ == '__main__':
    unittest.main()

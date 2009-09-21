
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
        self.app = QCoreApplication([])
        self.socket = QUdpSocket()
        self.socket.bind(45454)
        self.server = QUdpSocket()
        self.timer = QTimer.singleShot(1000, self.app.quit)
        self.a = QTimer.singleShot(100, self.broadcast)
        #self.a = QTimer()
        #self.a.setInterval(100)
        #QObject.connect(self.a, SIGNAL('timeout()'), self.broadcast)
        #self.a.start()

    def tearDown(self):
        #Release resources
        del self.socket
        del self.server
        del self.app

    def broadcast(self):
        addr = QHostAddress(QHostAddress.Broadcast)
        self.server.writeDatagram('datagram', addr, 45454)

    def callback(self):
        while self.socket.hasPendingDatagrams():
            datagram, host, port = self.socket.readDatagram(
                        self.socket.pendingDatagramSize())
            self.called = True
            self.app.quit()

    def testDefaultArgs(self):
        #QUdpSocket.readDatagram pythonic return
        # @bug 124
        QObject.connect(self.socket, SIGNAL('readyRead()'), self.callback)
        self.app.exec_()

        self.assert_(self.called)

if __name__ == '__main__':
    unittest.main()

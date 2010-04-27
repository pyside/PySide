//! [0]
def initSocket(self):
    udpSocket = QUdpSocket(self)
    udpSocket.bind(QHostAddress.LocalHost, 7755)

    self.connect(udpSocket, SIGNAL('readyRead()'),
                 self, SLOT('readPendingDatagrams()'))

def readPendingDatagrams(self):
    while udpSocket.hasPendingDatagrams():
        datagram = QByteArray()
        datagram.resize(udpSocket.pendingDatagramSize())

        (sender, senderPort) = udpSocket.readDatagram(datagram.data(), datagram.size())

        processTheDatagram(datagram)
//! [0]

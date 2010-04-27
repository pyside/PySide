//! [0]
socket.connectToHost("imap", 143)
if socket.waitForConnected(1000):
    print "Connected!"
//! [0]


//! [1]
socket.disconnectFromHost()
    if socket.state() == QAbstractSocket.UnconnectedState or \
        socket.waitForDisconnected(1000):
        print "Disconnected!"
//! [1]


//! [2]
class SocketClass(...):
    def readyReadSlot(self):
        # This slot is connected to QAbstractSocket::readyRead()
        while not socket.atEnd():
            data = socket.read(100)
            ...
//! [2]


//! [3]
socket.setProxy(QNetworkProxy.NoProxy)
//! [3]

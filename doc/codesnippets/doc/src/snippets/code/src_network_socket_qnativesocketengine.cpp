//! [0]
socketLayer = QNativeSocketEngine()
socketLayer.initialize(QAbstractSocket.TcpSocket, QAbstractSocket.IPv4Protocol)
socketLayer.connectToHost(QHostAddress.LocalHost, 22)
# returns False

socketLayer.waitForWrite()
socketLayer.connectToHost(QHostAddress.LocalHost, 22)
# returns True
//! [0]


//! [1]
socketLayer = QNativeSocketEngine()
socketLayer.bind(QHostAddress.Any, 4000)
socketLayer.listen()
if socketLayer.waitForRead():
    clientSocket = socketLayer.accept()
    # a client is connected

//! [1]

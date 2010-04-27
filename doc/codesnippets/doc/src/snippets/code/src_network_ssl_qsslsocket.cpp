//! [0]
socket = QSslSocket(self)
QObject.connect(socket, SIGNAL("encrypted()"), self, SLOT("ready()"))

socket.connectToHostEncrypted("imap.example.com", 993)
//! [0]


//! [1]
def incomingConnection(socketDescriptor):
    serverSocket = QSslSocket()
    if serverSocket.setSocketDescriptor(socketDescriptor):
        QObject.connect(serverSocket, SIGNAL("encrypted()"), self, SLOT("ready()"))
        serverSocket.startServerEncryption()
//! [1]


//! [2]
socket = QSslSocket()
socket.connectToHostEncrypted("http.example.com", 443)
if not socket.waitForEncrypted():
    print socket.errorString()
    return false

socket.write("GET / HTTP/1.0\r\n\r\n")
while socket.waitForReadyRead():
    print socket.readAll().data()
//! [2]


//! [3]
socket = QSslSocket()
QObject.connect(socket, SIGNAL("encrypted()"), receiver, SLOT("socketEncrypted()"))

socket.connectToHostEncrypted("imap", 993)
socket.write("1 CAPABILITY\r\n")
//! [3]


//! [4]
socket = QSslSocket()
socket.setCiphers("DHE-RSA-AES256-SHA:DHE-DSS-AES256-SHA:AES256-SHA")
//! [4]


//! [5]
socket.connectToHostEncrypted("imap", 993)
if socket.waitForEncrypted(1000):
    print "Encrypted!"
//! [5]

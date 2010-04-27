//! [0]
class MyThread (QThread):
    def run():
        socket = QTcpSocket()
        # connect QTcpSocket's signals somewhere meaningful
        # ...
        socket.connectToHost(hostName, portNumber)
        exec_()
//! [0]

//! [0]
gzip = QProcess()
gzip.start("gzip", ["-c"])
if not gzip.waitForStarted():
    return False

gzip.write("uncompressed data")

compressed = QByteArray()
while gzip.waitForReadyRead():
    compressed += gzip.readAll()
//! [0]


//! [1]
def bytesAvailable(self):
    return buffer.size() + QIODevice.bytesAvailable()
//! [1]


//! [2]
file = QFile("box.txt")
if file.open(QFile.ReadOnly):
    buf = file.readLine(1024)
    if buf.size():
        # the line is available in buf
//! [2]


//! [3]
def canReadLine(self):
    return buffer.contains('\n') or QIODevice.canReadLine()
//! [3]


//! [4]
def isExeFile(file_):
    buf = file_.peek(2)
    if buf.size() == 2:
        return buf[0] == 'M' and buf[1] == 'Z'
    return False
//! [4]


//! [5]
def isExeFile(file_):
    return file_.peek(2) == "MZ"
//! [5]

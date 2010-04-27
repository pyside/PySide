//! [0]
gzip = QProcess()
gzip.start("gzip", QStringList() << "-c")
if !gzip.waitForStarted():
    return false

gzip.write("uncompressed data");

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
    buf = file.readLine(1024);
    if buf.size():
        # the line is available in buf
//! [2]


//! [3]
def canReadLine(self):
    return buffer.contains('\n') || QIODevice.canReadLine()
//! [3]


//! [4]
def isExeFile(file):
    buf = file->peek(2);
    if buf.size() == 2:
        return (buf[0] == 'M' && buf[1] == 'Z')
    return false
//! [4]


//! [5]
def isExeFile(file):
    return file->peek(2) == "MZ"
//! [5]

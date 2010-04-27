//! [0]
file = QFile()
QDir.setCurrent("/tmp")
file.setFileName("readme.txt")
QDir.setCurrent("/home")
file.open(QIODevice.ReadOnly)       # opens "/home/readme.txt" under Unix
//! [0]


//! [1]
def myEncoderFunc(fileName):
//! [1]


//! [2]
def myDecoderFunc(localFileName):
//! [2]


//! [3]

def printError(msg):
    file = QFile()
    file.open(sys.stderr.fileno(), QIODevice.WriteOnly)
    file.write(msg, size(msg))                  # write to stderr
    file.close()
//! [3]


//! [4]
CONFIG += console
//! [4]

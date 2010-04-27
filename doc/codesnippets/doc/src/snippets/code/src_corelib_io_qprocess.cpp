
def wrapInFunction():

//! [0]
builder = QProcess()
builder.setProcessChannelMode(QProcess.MergedChannels)
builder.start("make", QStringList() << "-j2")

if !builder.waitForFinished():
    qDebug() << "Make failed:" << builder.errorString()
else
    qDebug() << "Make output:" << builder.readAll()
//! [0]


//! [1]
more = QProcess()
more.start("more")
more.write("Text to display")
more.closeWriteChannel()
#QProcess will emit readyRead() once "more" starts printing
//! [1]


//! [2]
command1 | command2
//! [2]


//! [3]
process1 = QProcess()
process2 = QProcess()

process1.setStandardOutputProcess(process2)

process1.start("command1")
process2.start("command2")
//! [3]


//! [4]
class SandboxProcess(QProcess):
    def setupChildProcess(self)
        # Drop all privileges in the child process, and enter
        # a chroot jail.
        os.setgroups(0, 0)
        os.chroot("/etc/safe")
        os.chdir("/")
        os.setgid(safeGid)
        os.setuid(safeUid)
        os.umask(0)

//! [4]


//! [5]
process = QProcess()
process.start("del /s *.txt")
# same as process.start("del", QStringList() << "/s" << "*.txt")
...
//! [5]


//! [6]
process = QProcess()
process.start("dir \"My Documents\"")
//! [6]


//! [7]
process = QProcess()
process.start("dir \"\"\"My Documents\"\"\"")
//! [7]


//! [8]
environment = QProcess.systemEnvironment()
# environment = {"PATH=/usr/bin:/usr/local/bin",
#                "USER=greg", "HOME=/home/greg"}
//! [8]



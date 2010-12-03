
void wrapInFunction()
{

//! [0]
QDir("/home/user/Documents")
QDir("C:/Documents and Settings")
//! [0]


//! [1]
QDir("images/landscape.png")
//! [1]


//! [2]
QDir("Documents/Letters/Applications").dirName() # "Applications"
QDir().dirName()                                 # "."
//! [2]


//! [3]
directory = QDir("Documents/Letters")
path = directory.filePath("contents.txt")
absolutePath = directory.absoluteFilePath("contents.txt")
//! [3]


//! [4]
dir = QDir("example")
if not dir.exists():
    print "Cannot find the example directory"
//! [4]


//! [5]
dir = QDir.root()                 # "/"
if not dir.cd("tmp"):             # "/tmp"
    print "Cannot find the \"/tmp\" directory"
else:
    file = QFile(dir.filePath("ex1.txt"))   # "/tmp/ex1.txt"
    if !file.open(QIODevice.ReadWrite):
        print "Cannot create the file %s" % (file.name())
//! [5]


//! [6]
bin = "/local/bin"         # where /local/bin is a symlink to /usr/bin
binDir = QDir(bin)
canonicalBin = binDir.canonicalPath()
# canonicalBin now equals "/usr/bin"

ls = "/local/bin/ls"       # where ls is the executable "ls"
lsDir = QDir(ls)
canonicalLs = lsDir.canonicalPath()
# canonicalLS now equals "/usr/bin/ls".
//! [6]


//! [7]
dir = QDir("/home/bob")

s = dir.relativeFilePath("images/file.jpg")         # s is "images/file.jpg"
s = dir.relativeFilePath("/home/mary/file.txt")     # s is "../mary/file.txt"
//! [7]


//! [8]
QDir.setSearchPaths("icons", [QDir.homePath() + "/images"])
QDir.setSearchPaths("docs", [":/embeddedDocuments"])
...
pixmap = QPixmap("icons:undo.png")  # will look for undo.png in QDir::homePath() + "/images"
file = QFile("docs:design.odf")     # will look in the :/embeddedDocuments resource path
//! [8]


//! [9]
dir = QDir("/tmp/root_link")
dir = dir.canonicalPath()
if dir.isRoot():
    print "It is a root link"
//! [9]


//! [10]
# The current directory is "/usr/local"
d1 = QDir("/usr/local/bin")
d2 = QDir("bin")
if d1 == d2:
    print "They're the same"
//! [10]


//! [11]
// The current directory is "/usr/local"
d1 = QDir("/usr/local/bin")
d1.setFilter(QDir.Executable)
d2 = QDir("bin")
if d1 != d2:
    print "They differ"
//! [11]


//! [12]
C:/Documents and Settings/Username
//! [12]


//! [13]
Q_INIT_RESOURCE(myapp);
//! [13]


//! [14]
def initMyResource():
    Q_INIT_RESOURCE(myapp)

class MyNamespace
    ...

    def myFunction(self):
        initMyResource()
//! [14]


//! [15]
Q_CLEANUP_RESOURCE(myapp);
//! [15]

}

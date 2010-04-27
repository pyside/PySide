//! [0]
class ZipEngineHandler(QAbstractFileEngineHandler)
    def create(fileName):
        # ZipEngineHandler returns a ZipEngine for all .zip files
        if fileName.toLower().endsWith(".zip"):
            return ZipEngine(fileName)
        else
            return None

def main():
    app = QApplication(sys.argv)

    engine = ZipEngineHandler()

    window = MainWindow()
    window.show()

    return app.exec()
//! [0]


//! [1]
def create(fileName):
    # ZipEngineHandler returns a ZipEngine for all .zip files
    if fileName.toLower().endsWith(".zip"):
        return ZipEngine(fileName)
    else
        return None
//! [1]


//! [2]
# @arg filters QDir.Filters
# @arg filterNames QStringList
# @return QAbstractFileEngineIterator
def beginEntryList(filters, filterNames):
    return CustomFileEngineIterator(filters, filterNames)
//! [2]


//! [3]
class CustomIterator(QAbstractFileEngineIterator):
    def __init__(self, nameFilters, filters):
        QAbstractFileEngineIterator.__init__(self, nameFilters, filters)

        self.index = 0
        # In a real iterator, these entries are fetched from the
        # file system based on the value of path().
        self.entries << "entry1" << "entry2" << "entry3"

    def hasNext(self):
        return self.index < self.entries.size() - 1

    def next(self):
       if !self.hasNext():
           return QString()
       index++
       return currentFilePath()

    def currentFileName(self):
       return self.entries.at(index)
//! [3]

//! [0]
lock = QReadWriteLock()

class ReaderThread:
    # ...
    def run():
        # ...
        lock.lockForRead()
        read_file()
        lock.unlock()
        # ...

class WriterThread:
    #...
    def run():
        # ...
        lock.lockForWrite()
        write_file()
        lock.unlock()
        # ...
//! [0]


//! [1]
lock = QReadWriteLock()

def readData():
    locker = QReadLocker(lock)
    # ...
    return data
//! [1]


//! [2]
lock = QReadWriteLock()

def readData():
    locker.lockForRead()
    # ...
    locker.unlock()
    return data
//! [2]


//! [3]
lock = QReadWriteLock()

def writeData(data):
    locker = QWriteLocker(lock)
    # ...
//! [3]


//! [4]
lock = QReadWriteLock()

def writeData(data):
    locker.lockForWrite()
    # ...
    locker.unlock()
//! [4]

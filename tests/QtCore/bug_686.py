from __future__ import with_statement

import unittest
from PySide.QtCore import *

class MyWriteThread(QThread):
    def __init__(self, lock):
        QThread.__init__(self)
        self.lock = lock
        self.started = False
        self.canQuit = False

    def run(self):
        self.started = True
        while not self.lock.tryLockForWrite():
            pass
        self.canQuit = True

class MyReadThread(QThread):
    def __init__(self, lock):
        QThread.__init__(self)
        self.lock = lock
        self.started = False
        self.canQuit = False

    def run(self):
        self.started = True
        while not self.lock.tryLockForRead():
            pass
        self.canQuit = True

class MyMutexedThread(QThread):
    def __init__(self, mutex):
        QThread.__init__(self)
        self.mutex = mutex
        self.started = False
        self.canQuit = False

    def run(self):
        self.started = True
        while not self.mutex.tryLock():
            pass
        self.canQuit = True

class TestQMutex (unittest.TestCase):

    def testReadLocker(self):
        lock = QReadWriteLock()
        thread = MyWriteThread(lock)

        with QReadLocker(lock):
            thread.start()
            while not thread.started:
                pass
            self.assertFalse(thread.canQuit)

        thread.wait()
        self.assertTrue(thread.canQuit)

    def testWriteLocker(self):
        lock = QReadWriteLock()
        thread = MyReadThread(lock)

        with QWriteLocker(lock):
            thread.start()
            while not thread.started:
                pass
            self.assertFalse(thread.canQuit)

        thread.wait()
        self.assertTrue(thread.canQuit)

    def testMutexLocker(self):
        mutex = QMutex()
        thread = MyMutexedThread(mutex)

        with QMutexLocker(mutex):
            thread.start()
            while not thread.started:
                pass
            self.assertFalse(thread.canQuit)

        thread.wait()
        self.assertTrue(thread.canQuit)

if __name__ == '__main__':
    unittest.main()

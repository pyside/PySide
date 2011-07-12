import time
import unittest

from PySide.QtCore import QTime, QRunnable, QThreadPool

class Task(QRunnable):
   def run(self):
       t = QTime()
       t.start()
       time.sleep(2) # Sleep 2 seconds


class QThreadPoolTest(unittest.TestCase):
    '''This used to cause a segfault due the ownership control on globalInstance function '''
    def testSlowJobs(self):
       for i in range(3):
           task = Task()
           QThreadPool.globalInstance().start(task)
           time.sleep(1) # Sleep 1 second

       QThreadPool.globalInstance().waitForDone()

if __name__ == '__main__':
    unittest.main()

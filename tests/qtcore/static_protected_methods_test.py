#!/usr/bin/python
'''Unit tests for static protected methods'''

import unittest, time

from PySide.QtCore import QThread

class Test (QThread):
    def run(self):
        start = time.time()
        self.sleep(1)
        self.time_elapsed = time.time() - start

class QStaticProtectedCall(unittest.TestCase):
    '''Test case for static protected method call'''

    def setUp(self):
        pass

    def tearDown(self):
        pass

    def testPathSeparator(self):
        thread = Test()
        thread.start()
        thread.wait()
        self.assertTrue(thread.time_elapsed <= 1.1) # tolarance of 100ms

if __name__ == '__main__':
    unittest.main()


'Tests for processtimer.py'

import unittest
import os

from subprocess import Popen, PIPE
from processtimer import TimeoutException, ProcessTimer

class TimeoutTest(unittest.TestCase):

    def tearDown(self):
        try:
            os.kill(self.proc.pid, 9)
        except OSError:
            pass

    def testRaise(self):
        self.proc = Popen(['python2.5', '-c', 'while True: pass' ], stdout=PIPE, stderr=PIPE)
        timer = ProcessTimer(self.proc, 1)
        self.assertRaises(TimeoutException, timer.waitfor)

class SimpleTest(unittest.TestCase):

    def tearDown(self):
        try:
            os.kill(self.proc.pid, 9)
        except OSError:
            pass
    def testSimple(self):
        self.proc = Popen(['python2.5', '-c', '"print"'], stdout=PIPE, stderr=PIPE)
        timer = ProcessTimer(self.proc, 10)
        timer.waitfor()

class TestEchoOutput(unittest.TestCase):

    def tearDown(self):
        try:
            os.kill(self.proc.pid, 9)
        except OSError:
            pass

    def testOutput(self):
        self.proc = Popen(['python2.5', '-c', 'print 1',], stdout=PIPE, stderr=PIPE)
        timer = ProcessTimer(self.proc, 1)
        timer.waitfor()
        self.assertEqual(self.proc.stdout.read().strip(), '1')

class TestRetCode(unittest.TestCase):

    def tearDown(self):
        try:
            os.kill(self.proc.pid, 9)
        except OSError:
            pass

    def testSimple(self):
        self.proc = Popen(['python2.5', '-c', 'print 1'], stdout=PIPE, stderr=PIPE)
        timer = ProcessTimer(self.proc, 10)
        timer.waitfor()

        self.assertEqual(self.proc.poll(), 0)


if __name__ == '__main__':
    unittest.main()

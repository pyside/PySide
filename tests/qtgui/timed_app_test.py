
import unittest

from helper import TimedQApplication 

class TestTimedApp(TimedQApplication):
    '''Simple test case for TimedQApplication'''

    def testFoo(self):
        #Simple test of TimedQApplication
        self.app.exec_()

if __name__ == '__main__':
    unittest.main()

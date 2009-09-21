
'''Test cases for passing invalid callbacks to QObject.connect'''

import unittest

from PySide.QtCore import QObject, SIGNAL

class InvalidCallback(unittest.TestCase):
    '''Test case for passing an invalid callback to QObject.connect'''

    def setUp(self):
        #Acquire resources
        self.obj = QObject()

    def tearDown(self):
        #Release resources
        try:
            del self.obj
        except AttributeError:
            pass

    def testIntegerCb(self):
        #Test passing an int as callback to QObject.connect
        self.assertRaises(TypeError, QObject.connect, self.obj,
                            SIGNAL('destroyed()'), 42)

if __name__ == '__main__':
    unittest.main()


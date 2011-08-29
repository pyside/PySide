from PySide.QtCore import QObject

import unittest


class TestBug987(unittest.TestCase):
    def callback(self):
        pass

    def testInvalidDisconnection(self):
        o = QObject()
        self.assertRaises(RuntimeError, o.destroyed.disconnect, self.callback)

if __name__ == '__main__':
    unittest.main()

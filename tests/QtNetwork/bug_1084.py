''' unit test for BUG #1084 '''

import unittest
from PySide import QtNetwork
import py3kcompat as py3k

class QTcpSocketTestCase(unittest.TestCase):
    def setUp(self):
        self.sock = QtNetwork.QTcpSocket()
        self.sock.connectToHost('127.0.0.1', 25)

    def testIt(self):
        self.sock.write(py3k.unicode_('quit'))

if __name__ == "__main__":
    unittest.main()

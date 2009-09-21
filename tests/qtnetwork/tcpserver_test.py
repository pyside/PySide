
'''Test cases for QTCPServer'''

import unittest

from PySide.QtNetwork import QTcpServer

class ListenDefaultArgsCase(unittest.TestCase):
    '''Test case for TcpServer.listen with default args'''

    def setUp(self):
        #Acquire resources
        self.server = QTcpServer()

    def tearDown(self):
        #Release resources
        del self.server

    def testDefaultArgs(self):
        # @bug 108
        #Default arguments for QTcpServer.listen
        self.server.listen()

if __name__ == '__main__':
    unittest.main()

#!/usr/bin/python
# -*- coding: utf-8 -*-
'''Tests QString implementation of Python buffer protocol'''

import unittest

from os.path import isdir
from PySide.QtCore import QString

class QStringBufferProtocolTest(unittest.TestCase):
    '''Tests QString implementation of Python buffer protocol'''

    def testQStringBufferProtocol(self):
        #Tests QString implementation of Python buffer protocol using the os.path.isdir
        #function which an unicode object or other object implementing the Python buffer protocol
        isdir(QString('/tmp'))

if __name__ == '__main__':
    unittest.main()


#!/usr/bin/python
# -*- coding: utf-8 -*-
'''Tests QByteArray implementation of Python buffer protocol'''

import unittest
import py3kcompat as py3k

from os.path import isdir
from PySide.QtCore import QByteArray


class QByteArrayBufferProtocolTest(unittest.TestCase):
    '''Tests QByteArray implementation of Python buffer protocol'''

    def testQByteArrayBufferProtocol(self):
        if py3k.IS_PY3K:
            return
        #Tests QByteArray implementation of Python buffer protocol using the os.path.isdir
        #function which an unicode object or other object implementing the Python buffer protocol
        isdir(QByteArray('/tmp'))

if __name__ == '__main__':
    unittest.main()


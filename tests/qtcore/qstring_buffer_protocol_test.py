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
        os_path_isdir_function_correctly_called_with_a_qstring = True
        try:
            isdir(QString('/tmp'))
        except:
            os_path_isdir_function_correctly_called_with_a_qstring = False
        self.assertTrue(os_path_isdir_function_correctly_called_with_a_qstring)

if __name__ == '__main__':
    unittest.main()


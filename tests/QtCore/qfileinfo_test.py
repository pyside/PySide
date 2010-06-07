
import unittest

import os
import tempfile

from PySide.QtCore import QFile, QFileInfo

class QFileConstructor(unittest.TestCase):
    '''QFileInfo constructor with qfile'''

    def testBasic(self):
        '''QFileInfo(QFile)'''
        obj = QFileInfo(QFile())

if __name__ == '__main__':
    unittest.main()

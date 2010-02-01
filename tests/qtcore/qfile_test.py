
import unittest

import os
import tempfile

from PySide.QtCore import QFile, QIODevice

class GetCharTest(unittest.TestCase):
    '''Test case for QIODevice.getChar in QFile'''

    def setUp(self):
        '''Acquire resources'''
        handle, self.filename = tempfile.mkstemp()
        os.write(handle, 'a')
        os.close(handle)

    def tearDown(self):
        '''release resources'''
        os.remove(self.filename)

    def testBasic(self):
        '''QFile.getChar'''
        obj = QFile(self.filename)
        obj.open(QIODevice.ReadOnly)
        self.assertEqual(obj.getChar(), (True, 'a'))
        self.assert_(not obj.getChar()[0])
        obj.close()

if __name__ == '__main__':
    unittest.main()


'''Test cases for QImage'''

import unittest

from PySide.QtGui import QImage

from helper import UsesQApplication

class QImageTest(UsesQApplication):
    '''Test case for calling setPixel with float as argument'''

    def testQImageStringBuffer(self):
        '''Test if the QImage signatures receiving string buffers exist.'''
        img0 = QImage('', 100, 100, QImage.Format_ARGB32)
        img1 = QImage('', 100, 100, 0, QImage.Format_ARGB32)

if __name__ == '__main__':
    unittest.main()



'''Test cases for QImage'''

import unittest
from PySide.QtGui import *
from helper import *

class QImageTest(UsesQApplication):
    '''Test case for calling setPixel with float as argument'''

    def testQImageStringBuffer(self):
        '''Test if the QImage signatures receiving string buffers exist.'''
        img0 = QImage(adjust_filename('sample.png', __file__))

        print type(img0.bits())

        # btw let's test the bits() method
        img1 = QImage(img0.bits(), img0.width(), img0.height(), img0.format())
        self.assertEqual(img0, img1)
        img2 = QImage(img0.bits(), img0.width(), img0.height(), img0.bytesPerLine(), img0.format())
        self.assertEqual(img0, img2)

        ## test scanLine method
        data1 = img0.scanLine(0)
        data2 = img1.scanLine(0)
        self.assertEqual(data1, data2)
        self.assertEquals(str(data1), img0.bits()[:img0.bytesPerLine()])
        self.assertEquals(str(data2), img0.bits()[:img0.bytesPerLine()])

if __name__ == '__main__':
    unittest.main()


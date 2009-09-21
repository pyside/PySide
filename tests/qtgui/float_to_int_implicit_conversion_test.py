
'''Test cases for QImage'''

import unittest

from PySide.QtGui import QImage, qRgb

from helper import UsesQApplication

class SetPixelFloat(UsesQApplication):
    '''Test case for calling setPixel with float as argument'''

    def setUp(self):
        #Acquire resources
        super(SetPixelFloat, self).setUp()
        self.color = qRgb(255, 0, 0)
        self.image = QImage(200, 200, QImage.Format_RGB32)

    def tearDown(self):
        #Release resources
        del self.color
        del self.image
        super(SetPixelFloat, self).tearDown()

    def testFloat(self):
        #QImage.setPixel(float, float, color) - Implicit conversion
        self.image.setPixel(3.14, 4.2, self.color)
        self.assertEqual(self.image.pixel(3.14, 4.2), self.color)


if __name__ == '__main__':
    unittest.main()

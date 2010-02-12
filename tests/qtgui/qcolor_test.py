
import unittest
import colorsys

from PySide.QtGui import QColor


class QColorGetTest(unittest.TestCase):

    def setUp(self):
        self.color = QColor(20, 40, 60, 80)

    def testGetRgb(self):
        self.assertEqual(self.color.getRgb(), (20, 40, 60, 80))

    def testGetRgbF(self):
        self.assertEqual(self.color.getRgbF(), (20.0/255, 40.0/255, 60.0/255, 80.0/255))

    def testGetHsl(self):
        hls = colorsys.rgb_to_hls(20.0/255, 40.0/255, 60.0/255)
        hsla = hls[0]*360.0, hls[2]*256, hls[1]*255, self.color.alpha()
        self.assertEqual(self.color.getHsl(), hsla)

    def testGetHslF(self):
        hls = colorsys.rgb_to_hls(20.0/255, 40.0/255, 60.0/255)
        hsla = hls[0], hls[2], hls[1], self.color.alphaF()
        for x, y in zip(self.color.getHslF(), hsla): # Due to rounding problems
            self.assert_(x - y < 1/100000.0)

    def testGetHsv(self):
        hsv = colorsys.rgb_to_hsv(20.0/255, 40.0/255, 60.0/255)
        hsva = int(hsv[0]*360.0), int(hsv[1]*255), int(hsv[2]*256), self.color.alpha()
        self.assertEqual(self.color.getHsv(), hsva)

    def testGetHsvF(self):
        hsv = colorsys.rgb_to_hsv(20.0/255, 40.0/255, 60.0/255)
        hsva = hsv[0], hsv[1], hsv[2], self.color.alphaF()
        self.assertEqual(self.color.getHsvF(), hsva)

    def testGetCmyk(self): # not supported by colorsys
        self.assertEqual(self.color.getCmyk(), (170, 85, 0, 195, 80))

    def testGetCmykF(self): # not supported by colorsys
        for x, y in zip(self.color.getCmykF(), (170/255.0, 85/255.0, 0, 195/255.0, 80/255.0)):
            self.assert_(x - y < 1/10000.0)


if __name__ == '__main__':
    unittest.main()

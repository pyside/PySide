
''' Test the presence of X11 symbols in QtGui'''

import unittest

from PySide.QtGui import *

class X11Test(unittest.TestCase):

    def test(self):
        qpixmapFuncs = dir(QPixmap)
        self.assert_('handle' in qpixmapFuncs)
        self.assert_('x11Info' in qpixmapFuncs)
        self.assert_('x11PictureHandle' in qpixmapFuncs)
        self.assert_('x11SetDefaultScreen' in qpixmapFuncs)

    def testX11Functions(self):
        qx11infoFuncs = dir(QX11Info)
        self.assert_('display' in qx11infoFuncs)
        self.assert_('appVisual' in qx11infoFuncs)
        self.assert_('visual' in qx11infoFuncs)

if __name__ == '__main__':
    unittest.main()

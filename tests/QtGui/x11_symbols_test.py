
''' Test the presence of X11 symbols in QtGui'''

import unittest

from PySide.QtGui import QPixmap

class X11Test(unittest.TestCase):

    def test(self):
        self.assert_('handle' in dir(QPixmap))
        self.assert_('x11Info' in dir(QPixmap))
        self.assert_('x11PictureHandle' in dir(QPixmap))
        self.assert_('x11SetDefaultScreen' in dir(QPixmap))

if __name__ == '__main__':
    unittest.main()


import unittest

from helper import TimedQApplication
from PySide.QtGui import QIcon


class QIconCtorWithNoneTest(TimedQApplication):
    '''Test made by seblin, see Bug #944: http://bugs.pyside.org/show_bug.cgi?id=944'''

    def testQIconCtorWithNone(self):
        icon = QIcon(None)
        pixmap = icon.pixmap(48, 48)
        self.app.exec_()

if __name__ == '__main__':
    unittest.main()

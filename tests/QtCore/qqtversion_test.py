
import unittest

from PySide import QtCore


class QQtVersionTest(unittest.TestCase):
    '''Tests for QtCore.QT_VERSION and QT_VERSION_STR'''

    def testVersion(self):
        self.assert_(hex(QtCore.QT_VERSION) > 0x40500)

    def testVersionStr(self):
        self.assert_(QtCore.QT_VERSION_STR)


if __name__ == '__main__':
    unittest.main()

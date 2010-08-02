
import unittest

from PySide import QtCore


class QAbsTest(unittest.TestCase):
    '''Tests for QtCore.qAbs'''

    def testBasic(self):
        def check(x):
            self.assertEqual(QtCore.qAbs(x), abs(x))

        check(0)
        check(-10)
        check(10)
        check(10.5)
        check(-10.5)

if __name__ == '__main__':
    unittest.main()

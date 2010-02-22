#!/usr/bin/python
'''Test cases for QFlags'''

import unittest
from PySide.QtCore import QIODevice, Qt, QFile

class QFLagTest(unittest.TestCase):
    '''Test case for usage of flags'''

    def testCallFunction(self):
        f = QFile("/tmp/t0");
        self.assertEqual(f.open(QIODevice.Truncate | QIODevice.Text | QIODevice.ReadWrite), True)
        om = f.openMode()
        self.assertEqual(om & QIODevice.Truncate, QIODevice.Truncate)
        self.assertEqual(om & QIODevice.Text, QIODevice.Text)
        self.assertEqual(om & QIODevice.ReadWrite, QIODevice.ReadWrite)
        self.assert_(om == QIODevice.Truncate | QIODevice.Text | QIODevice.ReadWrite)
        f.close()


class QFlagOperatorTest(unittest.TestCase):
    '''Test case for operators in QFlags'''

    def testInvert(self):
        '''QFlags ~ (invert) operator'''
        self.assert_(isinstance(~QIODevice.ReadOnly, QIODevice.OpenMode))

    def testOr(self):
        '''QFlags | (or) operator'''
        self.assert_(isinstance(QIODevice.ReadOnly | QIODevice.WriteOnly, QIODevice.OpenMode))

    def testAnd(self):
        '''QFlags & (and) operator'''
        self.assert_(isinstance(QIODevice.ReadOnly & QIODevice.WriteOnly, QIODevice.OpenMode))

    def testIOr(self):
        '''QFlags |= (ior) operator'''
        flag = Qt.WindowFlags()
        self.assert_(flag & Qt.Widget == 0)
        flag |= Qt.WindowMinimizeButtonHint
        self.assert_(flag & Qt.WindowMinimizeButtonHint)

    def testEqual(self):
        '''QFlags == operator'''
        flags = Qt.Window
        flags |= Qt.WindowMinimizeButtonHint
        flag_type = (flags & Qt.WindowType_Mask)
        self.assertEqual(flag_type, Qt.Window)


if __name__ == '__main__':
    unittest.main()

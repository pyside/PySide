#!/usr/bin/python
'''Test cases for QFlags'''

import unittest
from PySide.QtCore import *

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
        print (om != QIODevice.ReadOnly)
        f.close()


if __name__ == '__main__':
    unittest.main()

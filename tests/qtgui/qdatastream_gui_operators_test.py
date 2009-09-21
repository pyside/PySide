# -*- coding: utf-8 -*-

import unittest
import sys

from PySide import QtGui, QtCore


class QAppPresence(unittest.TestCase):

    def testQPixmap(self):
        ds = QtCore.QDataStream()
        p = QtGui.QPixmap()
        ds << p
        ds >> p

if __name__ == '__main__':
    app = QtGui.QApplication([])
    unittest.main()

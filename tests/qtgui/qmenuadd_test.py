# -*- coding: utf-8 -*-

''' Test the QMenu.addAction() method'''

import unittest
import sys

from PySide import QtGui

from helper import UsesQApplication

class QMenuAddAction(UsesQApplication):

    def openFile(self, *args):
        self.arg = args

    def testQMenuAddAction(self):
        fileMenu = QtGui.QMenu("&File")

        addNewAction = fileMenu.addAction("&Open...", self.openFile)
        addNewAction.trigger()
        self.assertEquals(self.arg, ())

if __name__ == '__main__':
    unittest.main()

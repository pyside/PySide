#!/usr/bin/python

'''Test cases for QTimer.singleShot'''

import unittest

from PySide.QtCore import QObject, QTimer, QCoreApplication, SIGNAL
from helper import UsesQCoreApplication

class TestDeleteLater(UsesQCoreApplication):
    '''Test case for function DeleteLater'''

    def testCase(self):
        o = QObject()
        o.deleteLater()
        del o
        QTimer.singleShot(100, self.app.quit)
        self.app.exec_()

if __name__ == '__main__':
    unittest.main()


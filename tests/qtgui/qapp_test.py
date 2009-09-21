
''' Test the presence of qApp Macro'''

import unittest

from PySide import QtGui

class QAppPresence(unittest.TestCase):

    def testQApp(self):
        #QtGui.qApp variable is instance of QApplication
        self.assert_(isinstance(QtGui.qApp, QtGui.QApplication))


if __name__ == '__main__':
    app = QtGui.QApplication([])
    unittest.main()

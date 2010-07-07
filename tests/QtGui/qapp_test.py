
''' Test the presence of qApp Macro'''

import unittest

from PySide.QtGui import *

class QAppPresence(unittest.TestCase):

    def testQApp(self):
        #QtGui.qApp variable is instance of QApplication
        self.assert_(isinstance(qApp, QApplication))

def main():
    app = QApplication([])
    unittest.main()

if __name__ == '__main__':
    main()

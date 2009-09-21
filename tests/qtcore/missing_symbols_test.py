
'''(Very) Simple test case for missing names from QtCore'''

import unittest
from PySide import QtCore

class MissingClasses(unittest.TestCase):

    def testQSettings(self): # Bug 232
        getattr(QtCore, 'QSettings')

    def testQtTrNoop(self): # Bug 220
        getattr(QtCore, 'QT_TR_NOOP')

if __name__ == '__main__':
    unittest.main()

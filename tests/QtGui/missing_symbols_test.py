
'''(Very) Simple test case for missing names from QtGui'''

import unittest
from PySide import QtGui

class MissingClasses(unittest.TestCase):
    def testQDrag(self): # Bug 222
        getattr(QtGui, 'QDrag')

    def testQDropEvent(self): # Bug 255
        getattr(QtGui, 'QDropEvent')

class MissingMembers(unittest.TestCase):

    def testQFontMetricsSize(self): # Bug 223
        QtGui.QFontMetrics.size

    def testQLayoutSetSpacing(self): # Bug 231
        QtGui.QLayout.setSpacing

    def testQImageLoad(self): # Bug 257
        QtGui.QImage.load

    def testQStandardItemModelinsertRow(self): # Bug 227
        QtGui.QStandardItemModel.insertRow

if __name__ == '__main__':
    unittest.main()

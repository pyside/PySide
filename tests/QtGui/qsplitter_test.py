import unittest
from PySide.QtGui import QSplitter

from helper import UsesQApplication

class QSplitterTest(UsesQApplication):

    def testGetRange(self):
        splitter = QSplitter()
        _min, _max = splitter.getRange(0)
        self.assert_(isinstance(_min, int))
        self.assert_(isinstance(_max, int))

if __name__ == "__main__":
   unittest.main()


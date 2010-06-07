'''Test cases for __hash__'''

import unittest

from PySide.QtGui import QTreeWidgetItem
from helper import UsesQApplication

class HashableTest(UsesQApplication):

    def testQTreeWidgetItemHash(self):
        h = {}
        obj = QTreeWidgetItem()
        h[obj] = 2
        self.assert_(h.get(obj), 2)

if __name__ == '__main__':
    unittest.main()


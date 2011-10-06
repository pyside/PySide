from PySide.QtCore import *
from PySide.QtGui import *
import unittest


class TestBug569(unittest.TestCase):

    def testIt(self):
        types = (QTableWidgetItem, QListWidgetItem, QTreeWidgetItem)
        for t in types:
            a = t()
            a.__lt__ = lambda other : True
            b = t()
            b.__lt__ = lambda other : False
            self.assertTrue(a < b)
            self.assertFalse(b < a)

if __name__ == '__main__':
    unittest.main()

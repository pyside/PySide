from PySide.QtCore import *
from PySide.QtGui import *
import unittest

class TestBugPYSIDE42 (unittest.TestCase):

    def testIt(self):
        obj1 = QFile()
        obj2 = QObject()
        hash1 = hash(obj1)
        hash2 = hash(obj2)

        self.assertNotEqual(hash1, hash2)
        self.assertEqual(hash1, hash(obj1))

if __name__ == '__main__':
    unittest.main()

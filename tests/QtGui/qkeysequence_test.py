import unittest

from PySide.QtCore import Qt
from PySide.QtGui import QKeySequence

from helper import UsesQApplication

class QKeySequenceTest(UsesQApplication):

    def testGetItemOperator(self):
        # bug #774
        ks = QKeySequence(Qt.SHIFT, Qt.CTRL, Qt.Key_P, Qt.Key_R)
        self.assertEqual(ks[0], Qt.SHIFT)
        self.assertEqual(ks[1], Qt.CTRL)
        self.assertEqual(ks[2], Qt.Key_P)
        self.assertEqual(ks[3], Qt.Key_R)


if __name__ == '__main__':
    unittest.main()

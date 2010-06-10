#!/usr/bin/python
import unittest
from PySide.QtCore import *

class QAnimationGroupTest(unittest.TestCase):

    def testBasic(self):
        app = QCoreApplication([])

        panim = QParallelAnimationGroup()
        sanim = QSequentialAnimationGroup()
        panim.addAnimation(sanim)

        self.assertEqual(sanim.parent(), panim)

        panim.clear()

        self.assertRaises(RuntimeError, lambda :sanim.parent())

        QTimer.singleShot(100, app.quit)
        app.exec_()

if __name__ == '__main__':
    unittest.main()

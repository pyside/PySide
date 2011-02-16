from PySide.QtCore import *
from PySide.QtGui import *
import unittest
import sys

class TestBug679(unittest.TestCase):
    '''QGraphicsScene::clear() is missing'''
    def testIt(self):
        app = QApplication([])

        scene = QGraphicsScene()
        hello = scene.addText("Hello")
        scene.addText("World")

        self.assertEqual(sys.getrefcount(hello), 3)
        scene.clear()
        self.assertEqual(sys.getrefcount(hello), 2)
        self.assertEqual(len(scene.items()), 0)
        self.assertRaises(RuntimeError, hello.isVisible) # the C++ object was deleted

if __name__ == '__main__':
    unittest.main()


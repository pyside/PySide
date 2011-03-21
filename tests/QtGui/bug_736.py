import unittest
from PySide.QtCore import *
from PySide.QtGui import *

class TestBug736 (unittest.TestCase):

    def testIt(self):
        app = QApplication([])
        slider = QSlider(Qt.Horizontal)
        slider2 = QSlider(Qt.Horizontal)

        slider2.setMaximum(10)
        slider.valueChanged[int].connect(slider2.setMaximum)
        slider.valueChanged[int].emit(100)
        self.assertEqual(slider2.maximum(), 100)


if __name__ == '__main__':
    unittest.main()

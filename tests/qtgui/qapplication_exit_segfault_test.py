
import unittest
import sys

from PySide.QtGui import QApplication, QPushButton, QWidget, QSpinBox

class QApplicationDelete(unittest.TestCase):
    '''Test for segfault when deleting a QApplication before a QWidget'''

    def testQPushButton(self):
        #QApplication deleted before QPushButton
        a = QApplication([])
        b = QPushButton('aaaa')
        del a

if __name__ == '__main__':
    unittest.main()

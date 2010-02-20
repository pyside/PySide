
import unittest

from PySide.QtCore import Qt
from PySide.QtGui import QPen

class QPenTest(unittest.TestCase):

    def testCtorWithCreatedEnums(self):
        '''A simple case of QPen creation using created enums.'''
        width = 0
        style = Qt.PenStyle(0)
        cap = Qt.PenCapStyle(0)
        join = Qt.PenJoinStyle(0)
        pen = QPen(Qt.blue, width, style, cap, join)


if __name__ == '__main__':
    unittest.main()


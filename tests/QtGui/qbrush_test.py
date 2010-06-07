
'''Test cases for QBrush'''

import unittest

from PySide.QtCore import Qt
from PySide.QtGui import QApplication, QColor, QBrush

from helper import UsesQApplication

class Constructor(UsesQApplication):
    '''Test case for constructor of QBrush'''

    def testQColor(self):
        #QBrush(QColor) constructor
        color = QColor('black')
        obj = QBrush(color)
        self.assertEqual(obj.color(), color)

        obj = QBrush(Qt.blue)
        self.assertEqual(obj.color(), Qt.blue)

if __name__ == '__main__':
    unittest.main()

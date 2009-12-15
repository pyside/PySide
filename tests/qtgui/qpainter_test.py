import unittest

from PySide.QtGui import QPainter, QBrush, QLinearGradient
from PySide.QtCore import QRect, Qt

class QPainterDrawText(unittest.TestCase):

    def setUp(self):
        self.painter = QPainter()
        self.text = 'teste!'

    def tearDown(self):
        del self.text
        del self.painter

    def testDrawText(self):
        # bug #254
        rect = self.painter.drawText(100, 100, 100, 100,
                                    Qt.AlignCenter | Qt.TextWordWrap,
                                    self.text)
        self.assertNotEqual(rect, None)

    def testDrawTextWithRect(self):
        # bug #225
        rect = QRect(100, 100, 100, 100)
        self.painter.drawText(rect, Qt.AlignCenter | Qt.TextWordWrap,
                              self.text)

class SetBrushWithOtherArgs(unittest.TestCase):
    '''Using qpainter.setBrush with args other than QBrush'''

    def testSetBrushGradient(self):
        painter = QPainter()
        gradient = QLinearGradient(0, 0, 0, 0)
        painter.setBrush(gradient)

if __name__ == '__main__':
    unittest.main()


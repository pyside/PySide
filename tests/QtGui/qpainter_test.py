import unittest

from PySide.QtGui import QPainter, QLinearGradient
from PySide.QtCore import QLine, QLineF, QPoint, QPointF, QRect, QRectF, Qt

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
        self.assert_(isinstance(rect, QRect))

    def testDrawTextWithRect(self):
        # bug #225
        rect = QRect(100, 100, 100, 100)
        newRect = self.painter.drawText(rect, Qt.AlignCenter | Qt.TextWordWrap,
                                        self.text)

        self.assert_(isinstance(newRect, QRect))

    def testDrawTextWithRectF(self):
        '''QPainter.drawText(QRectF, ... ,QRectF*) inject code'''
        rect = QRectF(100, 52.3, 100, 100)
        newRect = self.painter.drawText(rect, Qt.AlignCenter | Qt.TextWordWrap,
                                        self.text)

        self.assert_(isinstance(newRect, QRectF))

    def testDrawLinesOverloads(self):
        '''Calls QPainter.drawLines overloads, if something is
           wrong Exception and chaos ensues. Bug #395'''
        self.painter.drawLines([QLine(QPoint(0,0), QPoint(1,1))])
        self.painter.drawLines([QPoint(0,0), QPoint(1,1)])
        self.painter.drawLines([QPointF(0,0), QPointF(1,1)])
        self.painter.drawLines([QLineF(QPointF(0,0), QPointF(1,1))])

class SetBrushWithOtherArgs(unittest.TestCase):
    '''Using qpainter.setBrush with args other than QBrush'''

    def testSetBrushGradient(self):
        painter = QPainter()
        gradient = QLinearGradient(0, 0, 0, 0)
        painter.setBrush(gradient)

if __name__ == '__main__':
    unittest.main()


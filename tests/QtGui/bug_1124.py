''' unit test for BUG #1124 '''

import unittest
from PySide import QtGui, QtCore
import itertools

class TestBug1124(unittest.TestCase):
    def test_bug_1124(self):
        a = QtGui.QApplication([])
        allBlack = QtGui.QPixmap(10, 6)
        halfHalf = QtGui.QPixmap(2, 2)

        hhp = QtGui.QPainter(halfHalf)
        hhp.fillRect(QtCore.QRect(0, 0, 1, 2), QtGui.QColor.fromRgbF(0, 1, 0))
        hhp.fillRect(QtCore.QRect(1, 0, 1, 2), QtGui.QColor.fromRgbF(0, 0, 1))
        del hhp

        fragments = []
        mf = lambda *a, **kw: fragments.append(QtGui.QPainter.PixmapFragment.create(*a, **kw))

        mf(QtCore.QPointF(1, 1), QtCore.QRectF(0, 0, 2, 2))
        mf(QtCore.QPointF(3, 1), QtCore.QRectF(0, 0, 2, 2), rotation=90)
        mf(QtCore.QPointF(5, 1), QtCore.QRectF(0, 0, 2, 2), rotation=180)
        mf(QtCore.QPointF(7, 1), QtCore.QRectF(0, 0, 1, 1), scaleX=2, scaleY=2)
        mf(QtCore.QPointF(9, 1), QtCore.QRectF(1, 0, 1, 1), scaleX=2, scaleY=2)
        mf(QtCore.QPointF(1, 3), QtCore.QRectF(0, 0, 2, 2), opacity=0.5)
        mf(QtCore.QPointF(4, 4), QtCore.QRectF(0, 0, 2, 2), scaleX=2, scaleY=2)
        mf(QtCore.QPointF(8, 4), QtCore.QRectF(0, 0, 2, 2), scaleX=2, scaleY=2, rotation=90, opacity=0.5)

        allBlack.fill(QtGui.QColor("black"))

        abp = QtGui.QPainter(allBlack)
        abp.drawPixmapFragments(fragments, halfHalf)
        del abp

        image = allBlack.toImage()

        colors = {"G": QtGui.QColor.fromRgbF(0, 1, 0).rgb(),
                  "B": QtGui.QColor.fromRgbF(0, 0, 1).rgb(),
                  "g": QtGui.QColor.fromRgbF(0, 0.499, 0).rgb(),
                  "b": QtGui.QColor.fromRgbF(0, 0, 0.499).rgb(),
                  "0": QtGui.QColor("black").rgb()}

        lines = ["GBGGBGGGBB",
                 "GBBBBGGGBB",
                 "gbGGBBgggg",
                 "gbGGBBgggg",
                 "00GGBBbbbb",
                 "00GGBBbbbb"]

        for x, y in itertools.product(range(10), range(6)):
            c = colors[lines[y][x]]
            assert c == image.pixel(QtCore.QPoint(x, y))

        del a

if __name__ == "__main__":
    unittest.main()

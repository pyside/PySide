''' unit test for BUG #1124 '''

import unittest
from helper import UsesQApplication
from PySide import QtCore, QtGui
import sys

class MyWidget(QtGui.QWidget):
    def __init__(self, parent=None, app=None):
        super(MyWidget, self).__init__(parent)
        if not app:
            app = QApplication([])

        self.app = app

    def paintEvent(self, event):
        pa = QtGui.QPainter(self)
        fragments = []

        makeFragment = lambda *a, **kw: \
            fragments.append(QtGui.QPainter.PixmapFragment.create(*a, **kw))

        makeFragment(QtCore.QPointF(0, 0), QtCore.QRectF(0, 0, 2, 2))
        makeFragment(QtCore.QPointF(2, 0), QtCore.QRectF(0, 0, 2, 2),
                     rotation=90)
        makeFragment(QtCore.QPointF(4, 0), QtCore.QRectF(0, 0, 2, 2),
                     rotation=180)
        makeFragment(QtCore.QPointF(6, 0), QtCore.QRectF(0, 0, 1, 1),
                     scaleX=2, scaleY=2)
        makeFragment(QtCore.QPointF(8, 0), QtCore.QRectF(1, 0, 1, 1),
                     scaleX=2, scaleY=2)
        makeFragment(QtCore.QPointF(0, 2), QtCore.QRectF(0, 0, 2, 2),
                     opacity=0.5)
        makeFragment(QtCore.QPointF(2, 2), QtCore.QRectF(0, 0, 2, 2),
                     scaleX=2, scaleY=2)
        makeFragment(QtCore.QPointF(6, 2), QtCore.QRectF(0, 0, 2, 2),
                     scaleX=2, scaleY=2, rotation=90, opacity=0.5)

        try:
            pa.drawPixmapFragments(fragments, QtGui.QPixmap(2, 2), 0)
        except TypeError:
            sys.exit(-1)

        # test pa.drawPixmapFragments() by passing a tuple of integers rather
        # than QtGui.QPainter.PixmapFragment's that _must_ throw a TypeError
        # exception.
        try:
            pa.drawPixmapFragments((1, 2, 3), QtGui.QPixmap(2, 2), 0)
            sys.exit(-1) # it should not reach here
        except TypeError:
            pass

class QPainterTestCase(UsesQApplication):
    qapplication = True

    def setUp(self):
        super(QPainterTestCase, self).setUp()
        self.wid = MyWidget(app=self.app)

    def testIt(self):
        QtCore.QTimer.singleShot(200, self.app.quit)
        self.wid.show()
        self.app.exec_()

if __name__ == "__main__":
    unittest.main()

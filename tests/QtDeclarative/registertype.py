
import sys
import unittest
import helper
from PySide.QtCore import *
from PySide.QtGui import *
from PySide.QtDeclarative import *

class PieSlice (QDeclarativeItem):

    def __init__(self, parent = None):
        QDeclarativeItem.__init__(self, parent)
        # need to disable this flag to draw inside a QDeclarativeItem
        self.setFlag(QGraphicsItem.ItemHasNoContents, False)
        self._color = QColor()
        self._fromAngle = 0
        self._angleSpan = 0

    def getColor(self):
        return self._color

    def setColor(self, value):
        self._color = value

    def getFromAngle(self):
        return self._angle

    def setFromAngle(self, value):
        self._fromAngle = value

    def getAngleSpan(self):
        return self._angleSpan

    def setAngleSpan(self, value):
        self._angleSpan = value

    color = Property(QColor, getColor, setColor)
    fromAngle = Property(int, getFromAngle, setFromAngle)
    angleSpan = Property(int, getAngleSpan, setAngleSpan)

    def paint(self, painter, options, widget):
        global paintCalled
        pen = QPen(self._color, 2)
        painter.setPen(pen);
        painter.setRenderHints(QPainter.Antialiasing, True);
        painter.drawPie(self.boundingRect(), self._fromAngle * 16, self._angleSpan * 16);
        paintCalled = True

class PieChart (QDeclarativeItem):

    def __init__(self, parent = None):
        QDeclarativeItem.__init__(self, parent)
        self._name = ''
        self._slices = []

    def getName(self):
        return self._name

    def setName(self, value):
        self._name = value

    name = Property(str, getName, setName)

    def appendSlice(self, _slice):
        global appendCalled
        _slice.setParentItem(self)
        self._slices.append(_slice)
        appendCalled = True

    slices = ListProperty(PieSlice, append=appendSlice)

appendCalled = False
paintCalled = False

class TestQmlSupport(unittest.TestCase):

    def testIt(self):
        app = QApplication([])

        qmlRegisterType(PieChart, 'Charts', 1, 0, 'PieChart');
        qmlRegisterType(PieSlice, "Charts", 1, 0, "PieSlice");

        view = QDeclarativeView()
        view.setSource(QUrl.fromLocalFile(helper.adjust_filename('registertype.qml', __file__)))
        view.show()
        QTimer.singleShot(250, view.close)
        app.exec_()
        self.assertTrue(appendCalled)
        self.assertTrue(paintCalled)

if __name__ == '__main__':
    unittest.main()

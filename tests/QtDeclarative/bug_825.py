from PySide.QtCore import *
from PySide.QtGui import *
from PySide.QtDeclarative import *

from helper import adjust_filename
import unittest

paintCalled = False

class MetaA(type):
    pass

class A(object):
    __metaclass__ = MetaA

MetaB = type(QDeclarativeItem)
B = QDeclarativeItem

class MetaC(MetaA, MetaB):
    pass

class C(A, B):
    __metaclass__ = MetaC

class Bug825 (C):

    def __init__(self, parent = None):
        QDeclarativeItem.__init__(self, parent)
        # need to disable this flag to draw inside a QDeclarativeItem
        self.setFlag(QGraphicsItem.ItemHasNoContents, False)

    def paint(self, painter, options, widget):
        global paintCalled
        pen = QPen(Qt.black, 2)
        painter.setPen(pen);
        painter.drawPie(self.boundingRect(), 0, 128);
        paintCalled = True

class TestBug825 (unittest.TestCase):
    def testIt(self):
        global paintCalled
        app = QApplication([])
        qmlRegisterType(Bug825, 'bugs', 1, 0, 'Bug825')
        self.assertRaises(TypeError, qmlRegisterType, A, 'bugs', 1, 0, 'A')

        view = QDeclarativeView()
        view.setSource(QUrl.fromLocalFile(adjust_filename('bug_825.qml', __file__)))
        view.show()
        QTimer.singleShot(250, view.close)
        app.exec_()
        self.assertTrue(paintCalled)


if __name__ == '__main__':
    unittest.main()

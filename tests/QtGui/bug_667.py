from   PySide.QtCore import *
from   PySide.QtGui  import *

class Ball(QGraphicsEllipseItem):
    def __init__(self, d, parent=None):
        super(Ball, self).__init__(0, 0, d, d, parent)
        self.vel = QPointF(0,0)   #commenting this out prevents the crash

class Foo(QGraphicsView):
    def __init__(self):
        super(Foo, self).__init__(None)
        self.scene = QGraphicsScene(self.rect())
        self.setScene(self.scene)
        self.scene.addItem(Ball(10))


if __name__ == "__main__":
    import sys
    app = QApplication(sys.argv)
    w = Foo()
    w.show()
    w.raise_()
    QTimer.singleShot(0, w.close)
    sys.exit(app.exec_())

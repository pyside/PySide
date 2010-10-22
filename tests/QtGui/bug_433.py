from PySide import QtCore, QtGui
import sys

class Test(QtGui.QGraphicsView):
    def __init__(self, parent=None):
        super(Test, self).__init__(parent)
        self.s = QtGui.QGraphicsScene()
        self.setScene(self.s)

a = QtGui.QApplication(sys.argv)
t = Test()
t.show()
QtCore.QTimer.singleShot(0, t.close)
sys.exit(a.exec_())

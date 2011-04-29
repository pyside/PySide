from PySide import QtCore, QtGui

class Window(QtGui.QMainWindow):
    def childEvent(self, event):
        super(Window, self).childEvent(event)

app = QtGui.QApplication([])
window = Window()

dock1 = QtGui.QDockWidget()
dock2 = QtGui.QDockWidget()
window.addDockWidget(QtCore.Qt.LeftDockWidgetArea, dock1)
window.addDockWidget(QtCore.Qt.LeftDockWidgetArea, dock2)
window.tabifyDockWidget(dock1, dock2)

window.show()
QtCore.QTimer.singleShot(0, window.close)
app.exec_()

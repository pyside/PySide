from helper import adjust_filename
from PySide import QtGui, QtCore
from PySide.QtUiTools import QUiLoader

class View_1(QtGui.QWidget):

    def __init__(self):
        QtGui.QWidget.__init__(self)
        loader = QUiLoader()
        widget = loader.load(adjust_filename('bug_552.ui', __file__), self)
        self.children = []
        for child in widget.findChildren(QtCore.QObject, None):
            self.children.append(child)
        self.t = widget.tabWidget
        self.t.removeTab(0)

app = QtGui.QApplication([])
window = View_1()
window.show()

# If it doesn't crash it works :-)

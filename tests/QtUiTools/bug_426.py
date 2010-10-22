import sys
import os
from PySide import QtCore, QtGui
from PySide.QtUiTools import QUiLoader

class Window(object):
    def __init__(self):
        loader = QUiLoader()
        filePath = os.path.join(os.path.dirname(__file__), 'bug_426.ui')
        self.widget = loader.load(filePath)
        self.group = QtGui.QActionGroup(self.widget)
        self.widget.show()
        QtCore.QTimer.singleShot(0, self.widget.close)

if __name__ == "__main__":
    app = QtGui.QApplication(sys.argv)
    win = Window()
    sys.exit(app.exec_())

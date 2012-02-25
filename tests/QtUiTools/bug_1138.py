from PySide import QtCore, QtGui
from PySide.QtUiTools import QUiLoader
from helper import adjust_filename

class MyQUiLoader(QUiLoader):
    def __init__(self):
        super(MyQUiLoader, self).__init__()

    def createLayout(self, *args):
        return super(MyQUiLoader, self).createLayout(*args)

if __name__ == "__main__":
    app = QtGui.QApplication([])

    ui = MyQUiLoader().load(adjust_filename("bug_1138.ui", __file__))

    label = QtGui.QLabel("test")
    ui.verLayout.addWidget(label)
    ui.show()

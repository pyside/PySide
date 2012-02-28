''' unit test for BUG #1135 '''
''' see http://bugs.pyside.org/show_bug.cgi?id=1135 '''

from PySide.QtCore import *
from PySide.QtGui import *
from PySide.QtUiTools import QUiLoader
from helper import adjust_filename

class CustomWidget(QFrame):
    def __init__(self, parent=None):
        super(CustomWidget, self).__init__(parent)
        self.layout = QVBoxLayout()
        self.label = QLabel("Custom widget")
        self.layout.addWidget(self.label)
        self.setLayout(self.layout)

class CustomLoader(QUiLoader):
    def __init__(self):
        super(CustomLoader,self).__init__()

    def createWidget(self, className, parent=None, name=""):
        return super(CustomLoader, self).createWidget(className, parent, name)

if __name__ == "__main__":
    app = QApplication([])
    loader = CustomLoader()
    loader.registerCustomWidget(CustomWidget)
    form = loader.load(adjust_filename("bug_1135.ui", __file__))
    form.show()

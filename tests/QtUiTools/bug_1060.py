''' unit test for BUG #1060 '''

from PySide.QtGui import QApplication
from PySide.QtUiTools import QUiLoader
from helper import adjust_filename

class MyQUiLoader(QUiLoader):
    def __init__(self):
        super(MyQUiLoader, self).__init__()

    def createWidget(self, *args):
        return super(MyQUiLoader, self).createWidget(*args)

if __name__ == "__main__":
    app = QApplication([])

    ui = MyQUiLoader().load(adjust_filename("bug_1060.ui", __file__))
    ui.show()

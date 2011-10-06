from PySide.QtGui import *
from PySide.QtDeclarative import *
from helper import adjust_filename, UsesQApplication

app = QApplication([])
view = QDeclarativeView(adjust_filename('bug_995.qml', __file__))
view.show()
view.resize(200, 200)
item = view.itemAt(100, 100)

# it CAN NOT crash here
print(item)


import sys
from PySide.QtCore import *
from PySide.QtGui import *

class ListModel(QAbstractListModel):
    def rowCount(self, parent = QModelIndex()):
        return 0

app = QApplication([])
model = ListModel()
v = QListView()
v.setModel(model)
QTimer.singleShot(0, v.close)
app.exec_()

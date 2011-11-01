from PySide.QtGui import *
from PySide.QtCore import *

class QtKeyPressListener(QObject):
    def __init__(self, obj):
        QObject.__init__(self)
        obj.installEventFilter(self)

    def eventFilter(self, obj, event):
        # This used to crash here due to a misbehaviour of type discovery!
        return QObject.eventFilter(self, obj, event)

app = QApplication([])
key_listener = QtKeyPressListener(app)
w = QLabel('Hello')
w.show()
QTimer.singleShot(0, w.close)
app.exec_()

from PySide.QtCore import *
from PySide.QtGui import *
import sys

app = QApplication(sys.argv)
scene = QGraphicsScene()
label = QLabel("hello world")
label.show()
QTimer.singleShot(0, label.close)
exit(app.exec_())

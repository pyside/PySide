from PySide.QtGui import *
from PySide.QtCore import *
import os

if "DISPLAY" in os.environ:
    del os.environ["DISPLAY"]

app = QApplication([], False)
QTimer.singleShot(0, app.quit)
app.exec_()




from PySide.QtGui import *
from PySide.QtCore import *

app = QApplication([])
QTimer.singleShot(200, app.quit)

# This test for a dead lock in QFileDialog.getOpenFileNames, the test fail with a timeout if the dead lock exists.
QFileDialog.getOpenFileNames(None, "caption", QDir.homePath(), None, "", QFileDialog.DontUseNativeDialog)

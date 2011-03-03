
//! [using a custom style]
import sys
from PySide.QtGui import *

QApplication.setStyle(CustomStyle())
app = QApplication(sys.argv)
spinBox = QSpinBox()
spinBox.show()
sys.exit(app.exec_())

//! [using a custom style]

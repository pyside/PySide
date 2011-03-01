
from PySide.QtCore import *
from PySide.QtGui import *
from PySide.QtWebKit import *
import sys

app = QApplication(sys.argv)
parent = None
//! [Using QWebView]
view = QWebView(parent)
view.load(QUrl("http://qt.nokia.com/"))
view.show()
//! [Using QWebView]
sys.exit(app.exec_())

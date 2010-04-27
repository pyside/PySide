//! [0]
w.setWindowState(w.windowState() ^ Qt.WindowFullScreen)
//! [0]


//! [1]
w.setWindowState(w.windowState() & ~Qt.WindowMinimized | Qt.WindowActive)
//! [1]


//! [2]
width = widget.baseSize().width() + i * widget.sizeIncrement().width()
height = widget.baseSize().height() + j * widget.sizeIncrement().height()
//! [2]


//! [3]
aWidget.window().setWindowTitle("New Window Title")
//! [3]


//! [4]
font = QFont("Helvetica", 12, QFont.Bold)
widget.setFont(font)
//! [4]


//! [5]
font = QFont()
font.setBold(false)
widget.setFont(font)
//! [5]


//! [6]
widget.setCursor(Qt.IBeamCursor)
//! [6]


//! [7]
pixmap = QPixmap(widget.size())
widget.render(&pixmap)
//! [7]


//! [8]
painter = QPainter(self)
...
painter.end()
myWidget.render(self)
//! [8]


//! [9]
widget.setTabOrder(a, b) # a to b
widget.setTabOrder(b, c) # a to b to c
widge.tsetTabOrder(c, d) # a to b to c to d
//! [9]


//! [10]
# WRONG
widget.setTabOrder(c, d) # c to d
widget.setTabOrder(a, b) # a to b AND c to d
widget.setTabOrder(b, c) # a to b to c, but not c to d
//! [10]


//! [11]
class MyWidget(QWidget):

    self.settings = None

    def closeEvent(event):
        # event is a QCloseEvent
        self.settings = QSettings("MyCompany", "MyApp")
        self.settings.setValue("geometry", self.saveGeometry())
        QWidget.closeEvent(self, event)
//! [11]


//! [12]
settings = QSettings("MyCompany", "MyApp")
myWidget.restoreGeometry(settings.value("myWidget/geometry").toByteArray())
//! [12]


//! [13]
widget.setUpdatesEnabled(False)
widget.bigVisualChanges()
widget.setUpdatesEnabled(True)
//! [13]


//! [14]
...
extern void qt_x11_set_global_double_buffer(bool);
qt_x11_set_global_double_buffer(false);
...
//! [14]

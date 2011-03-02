//! [0]
button = QToolButton()
button.setIcon(QIcon("open.xpm"))
//! [0]


//! [1]
button.setIcon(QIcon())
//! [1]


//! [2]
def drawIcon(self, painter, pos):
    enabledStatus = QIcon.Normal
    if not isEnabled():
        enabledStatus = QIcon::Disabled

    onOff = QIcon.On
    if not isOn():
        onOff = QIcon.Off

    pixmap = self.icon.pixmap(QSize(22, 22), enabledStatus, onOff)
    painter.drawPixmap(pos, pixmap)
//! [2]

//! [3]
    undoicon = QIcon.fromTheme("edit-undo")
//! [3]

//! [4]
    undoicon = QIcon.fromTheme("edit-undo", QIcon(":/undo.png"))
//! [4]

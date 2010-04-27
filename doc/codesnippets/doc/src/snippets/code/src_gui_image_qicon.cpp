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
    if !isEnabled():
        enabledStatus = QIcon::Disabled

    onOff = QIcon.On
    if !isOn():
        onOff = QIcon.Off

    pixmap = icon.pixmap(QSize(22, 22),
                        enabledStatus,
                        onOff)
    painter.drawPixmap(pos, pixmap)
//! [2]

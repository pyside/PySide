//! [0]
def contextMenuEvent(event):
    menu = createStandardContextMenu()
    menu.addAction(QObject.tr("My Menu Item"))
    #...
    menu.exec_(event.globalPos())
//! [0]

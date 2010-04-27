//! [0]
class MyQPlainTextEdit(QPlainTextEdit):
    def contextMenuEvent(self, event):
        menu = createStandardContextMenu()
        menu.addAction(tr("My Menu Item"))
        # ...
        menu.exec_(event.globalPos())
        del menu
//! [0]


//! [1]
edit.textCursor().insertText(text)
//! [1]

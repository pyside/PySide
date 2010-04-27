//! [0]
cursor.clearSelection()
cursor.movePosition(QTextCursor.NextWord, QTextCursor.KeepAnchor)
cursor.insertText("Hello World")
//! [0]


//! [1]
img = ... # A QImage
textDocument.addResource(QTextDocument.ImageResource, QUrl("myimage"), img)
cursor.insertImage("myimage")
//! [1]


//! [2]
cursor = QTextCursor(textDocument)
cursor.beginEditBlock()
cursor.insertText("Hello")
cursor.insertText("World")
cursor.endEditBlock()

textDocument.undo()
//! [2]


//! [3]
cursor = QTextCursor(textDocument)
cursor.beginEditBlock()
cursor.insertText("Hello")
cursor.insertText("World")
cursor.endEditBlock()

...

cursor.joinPreviousEditBlock()
cursor.insertText("Hey")
cursor.endEditBlock()

textDocument.undo()
//! [3]

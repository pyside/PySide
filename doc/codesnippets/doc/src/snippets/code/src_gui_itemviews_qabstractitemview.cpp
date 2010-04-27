//! [0]
def resizeEvent(self, event):
    horizontalScrollBar().setRange(0, realWidth - width())
    ...
//! [0]

//! [1]
setIndexWidget(index, QLineEdit())
...
setIndexWidget(index, QTextEdit())
//! [1]

//! [2]
m = view->selectionModel()
view->setModel(model())
del m
//! [2]

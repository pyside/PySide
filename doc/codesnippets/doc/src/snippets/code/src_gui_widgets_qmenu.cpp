//! [0]
exec_(QCursor.pos())
//! [0]


//! [1]
exec_(somewidget.mapToGlobal(QPoint(0,0)))
//! [1]


//! [2]
exec_(e.globalPos())
//! [2]


//! [3]
exec_(QCursor.pos())
//! [3]


//! [4]
exec_(somewidget.mapToGlobal(QPoint(0, 0)))
//! [4]


//! [5]
exec_(e.globalPos())
//! [5]


//! [6]
menu = QMenu()
at = actions[0] // Assumes actions is not empty
for a in actions:
    menu.addAction(a)
menu.exec_(pos, at)
//! [6]

//! [0]
QKeySequence(QKeySequence.Print)
QKeySequence(tr("Ctrl+P"))
QKeySequence(tr("Ctrl+p"))
QKeySequence(Qt.CTRL + Qt.Key_P)
//! [0]


//! [1]
QKeySequence(tr("Ctrl+X, Ctrl+C"))
QKeySequence(Qt.CTRL + Qt.Key_X, Qt.CTRL + Qt.Key_C)
//! [1]


//! [2]
file = QMenu(self)
file.addAction(tr("&Open..."), self, SLOT("open()"),
               QKeySequence(tr("Ctrl+O", "File|Open")))
//! [2]

//! [0]
button = QPushButton(QObject.tr("Ro&ck && Roll"), self)
//! [0]


//! [1]
button.setIcon(QIcon(":/images/print.png"))
button.setShortcut(tr("Alt+F7"))
//! [1]


//! [2]
class MyWidget (QWidget):
    #...
    def reactToToggle(checked):
        if checked:
            // Examine the button states.
            ...
//! [2]

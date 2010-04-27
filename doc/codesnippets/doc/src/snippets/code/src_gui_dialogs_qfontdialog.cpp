//! [0]

(ok, font) = QFontDialog.getFont(QFont("Helvetica [Cronyx]", 10), self)
if ok:
    # the user clicked OK and font is set to the font the user selected
else:
    # the user canceled the dialog; font is set to the initial
    # value, in this case Helvetica [Cronyx], 10
//! [0]


//! [1]
myWidget.setFont(QFontDialog.getFont(0, myWidget.font()))
//! [1]


//! [2]
(ok, font) = QFontDialog.getFont(QFont("Times", 12), self)
if ok:
    # font is set to the font the user selected
else:
    # the user canceled the dialog; font is set to the initial
    # value, in this case Times, 12.
//! [2]


//! [3]
myWidget.setFont(QFontDialog.getFont(0, myWidget.font()))
//! [3]


//! [4]

(ok, font) = QFontDialog.getFont(self)
if ok:
    # font is set to the font the user selected
else:
    # the user canceled the dialog; font is set to the default
    # application font, QApplication.font()
//! [4]

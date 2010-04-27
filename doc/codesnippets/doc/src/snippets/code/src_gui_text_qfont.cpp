//! [0]
serifFont = QFont("Times", 10, QFont.Bold)
sansFont = QFont("Helvetica [Cronyx]", 12)
//! [0]


//! [1]
f = QFont("Helvetica")
//! [1]


//! [2]
f = QFont("Helvetica [Cronyx]")
//! [2]


//! [3]
info = QFontInfo(f1)
family = info.family()
//! [3]


//! [4]
fm = QFontMetrics(f1)
textWidthInPixels = fm.width("How many pixels wide is this text?")
textHeightInPixels = fm.height()
//! [4]

//! [0]
font = QFont("times", 24)
fm = QFontMetrics(font)
pixelsWide = fm.width("What's the width of this text?")
pixelsHigh = fm.height()
//! [0]


//! [1]
font = QFont("times", 24)
fm = QFontMetricsF(font)
pixelsWide = fm.width("What's the width of this text?")
pixelsHigh = fm.height()
//! [1]

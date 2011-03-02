//! [0]
static const char * const start_xpm[]={
    "16 15 8 1",
    "a c #cec6bd",
....
//! [0]


//! [1]
myPixmap = QPixmap()
myPixmap.setMask(myPixmap.createHeuristicMask())
//! [1]

//! [2]
pixmap = QPixmap("background.png")
exposed = QRegion()
pixmap.scroll(10, 10, pixmap.rect(), exposed)
//! [2]

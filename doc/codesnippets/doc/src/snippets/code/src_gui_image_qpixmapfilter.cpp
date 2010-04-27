//! [0]
myFilter = QPixmapColorFilter()
myFilter.setColor(QColor(128, 0, 0))
myFilter.draw(painter, QPoint(0, 0), originalPixmap)
//! [0]

//! [1]
myFilter = QPixmapConvolutionFilter()
kernel = [
     0.0,-1.0, 0.0,
    -1.0, 5.0,-1.0,
     0.0,-1.0, 0.0
    ]
myFilter.setConvolutionKernel(kernel, 3, 3)
myFilter.sdraw(painter, QPoint(0, 0), originalPixmap)
//! [1]

//! [2]
myFilter = QPixmapDropShadowFilter()
myFilter.draw(painter, QPoint(0, 0), originalPixmap)
//! [2]


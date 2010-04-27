//! [0]
class Widget:
    def mousePressEvent(self, event):
        origin = event.pos()
        if not self.rubberBand:
            self.rubberBand = QRubberBand(QRubberBand.Rectangle, self)
        rubberBand.setGeometry(QRect(origin, QSize()))
        rubberBand.show()

    def mouseMoveEvent(self, event):
        rubberBand.setGeometry(QRect(origin, event.pos()).normalized())

    def mouseReleaseEvent(self, event):
        rubberBand.hide()
        # determine selection, for example using QRect.intersects()
        # and QRect.contains().
//! [0]

//! [0]
class MyWidget (QWidget):
    # ...
    def paintEvent(self):
        r1 = QRegion(QRect(100, 100, 200, 80), QRegion.Ellipse) # r1: elliptic region
                )
        r2 = QRect(100, 120, 90, 30)   # r2: rectangular region
        r3 = r1.intersected(r2)        # r3: intersection

        painter = QPainter(self)
        painter.setClipRegion(r3)
        ...                            # paint clipped graphics
//! [0]

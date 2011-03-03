//! [0]
def draw(self, painter):
    # Fully opaque draw directly without going through a pixmap.
    if qFuzzyCompare(self.opacity, 1):
        drawSource(painter)
        return
    # ...
//! [0]

//! [1]
def draw(self, painter):
    # ...
    offset = QPoint()
    if self.sourceIsPixmap():
        # No point in drawing in device coordinates (pixmap will be scaled anyways).
        pixmap = sourcePixmap(Qt.LogicalCoordinates, offset)
        ...
        painter.drawPixmap(offset, pixmap)
    else:
        # Draw pixmap in device coordinates to avoid pixmap scaling
        pixmap = sourcePixmap(Qt.DeviceCoordinates, offset)
        painter.setWorldTransform(QTransform())
        # ...
        painter.drawPixmap(offset, pixmap)
    # ...
//! [1]

//! [2]
# ...
alphaGradient = QLinearGradient(rect.topLeft(), rect.bottomLeft())
alphaGradient.setColorAt(0.0, Qt.transparent)
alphaGradient.setColorAt(0.5, Qt.black)
alphaGradient.setColorAt(1.0, Qt.transparent)
effect = QGraphicsOpacityEffect()
effect.setOpacityMask(alphaGradient)
# ...
//! [2]

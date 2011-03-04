//![0]
class ColorImageProvider (QDeclarativeImageProvider):
    def __init__(self):
        QDeclarativeImageProvider.__init__(self, QDeclarativeImageProvider.Pixmap)

    def requestPixmap(id, size, requestedSize):
        width = 100
        height = 50

        if size:
            size.setWidth(width)
            size.setHeight(height)

        if requestedSize.width() > 0:
            width = requestedSize.width()
        if requestedSize.height() > 0:
            height = requestedSize.height()

        pixmap = QPixmap(width, height)
        pixmap.fill(QColor(id).rgba())
//![0]
        # write the color name
        painter = QPainter(pixmap)
        f = painter.font()
        f.setPixelSize(20)
        painter.setFont(f)
        painter.setPen(Qt.black)
        if requestedSize.isValid():
            painter.scale(requestedSize.width() / width, requestedSize.height() / height)
        painter.drawText(QRectF(0, 0, width, height), Qt.AlignCenter, id)
//![1]
        return pixmap
//![1]

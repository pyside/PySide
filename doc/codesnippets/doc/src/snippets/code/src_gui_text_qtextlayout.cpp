//! [0]
leading = fontMetrics.leading()
height = 0
widthUsed = 0
textLayout.beginLayout()
while True:
    line = textLayout.createLine()
    if not line.isValid():
        break

    line.setLineWidth(lineWidth)
    height += leading
    line.setPosition(QPointF(0, height))
    height += line.height()
    widthUsed = qMax(widthUsed, line.naturalTextWidth())
textLayout.endLayout()
//! [0]


//! [1]
painter  = QPainter(self)
textLayout.draw(painter, QPoint(0, 0))
//! [1]

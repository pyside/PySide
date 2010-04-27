//! [0]
path = QPainterPath()
path.addRect(20, 20, 60, 60)

path.moveTo(0, 0)
path.cubicTo(99, 0,  50, 50,  99, 99)
path.cubicTo(0, 99,  50, 50,  0, 0)

QPainter painter(self)
painter.fillRect(0, 0, 100, 100, Qt.white)
painter.setPen(QPen(QColor(79, 106, 25), 1, Qt.SolidLine,
                    Qt.FlatCap, Qt.MiterJoin))
painter.setBrush(QColor(122, 163, 39))

painter.drawPath(path)
//! [0]


//! [1]
myGradient = QLinearGradient()
myPen = QPen()

myPath = QPainterPath()
myPath.cubicTo(c1, c2, endPoint)

painter = QPainter(self)
painter.setBrush(myGradient)
painter.setPen(myPen)
painter.drawPath(myPath)
//! [1]


//! [2]
myGradient = QLinearGradient()
myPen = QPen()

startPoint = QPointF()
center = QPointF()

myPath = QPainterPath()
myPath.moveTo(center)
myPath.arcTo(boundingRect, startAngle,
             sweepLength)

painter = QPainter(self)
painter.setBrush(myGradient)
painter.setPen(myPen)
painter.drawPath(myPath)
//! [2]


//! [3]
myGradient = QLinearGradient()
myPen = QPen()
myRectangle = QRectF()

myPath = QPainterPath()
myPath.addRect(myRectangle)

painter = QPainter(self)
painter.setBrush(myGradient)
painter.setPen(myPen)
painter.drawPath(myPath)
//! [3]


//! [4]
myGradient = QLinearGradient()
myPen = QPen()
myPolygon = QPolygonF()

myPath = QPainterPath()
myPath.addPolygon(myPolygon)

QPainter painter(self)
painter.setBrush(myGradient)
painter.setPen(myPen)
painter.drawPath(myPath)
//! [4]


//! [5]
myGradient = QLinearGradient()
myPen = QPen()
boundingRectangle = QRectF()

myPath = QPainterPath()
myPath.addEllipse(boundingRectangle)

QPainter painter(self)
painter.setBrush(myGradient)
painter.setPen(myPen)
painter.drawPath(myPath)
//! [5]


//! [6]
myGradient = QLinearGradient()
myPen = QPen()
myFont = QFont()
QPointF baseline(x, y)

myPath = QPainterPath()
myPath.addText(baseline, myFont, tr("Qt"))

painter QPainter(self)
painter.setBrush(myGradient)
painter.setPen(myPen)
painter.drawPath(myPath)
//! [6]

//! [0]
painter = QPainter(self)
pen = QPen(Qt.green, 3, Qt.DashDotLine, Qt.RoundCap, Qt.RoundJoin)
painter.setPen(pen)
//! [0]


//! [1]
painter = QPainter(self)
pen = QPen()  # creates a default pen

pen.setStyle(Qt.DashDotLine)
pen.setWidth(3)
pen.setBrush(Qt.green)
pen.setCapStyle(Qt.RoundCap)
pen.setJoinStyle(Qt.RoundJoin)

painter.setPen(pen)
//! [1]


//! [2]
pen = QPen()
space = 4;
dashes = [1, space, 3, space, 9, space, 27, space, 9, space]
pen.setDashPattern(dashes)
//! [2]


//! [3]
pen = QPen()
space = 4;
dashes = [1, space, 3, space, 9, space, 27, space, 9, space]
pen.setDashPattern(dashes)
//! [3]

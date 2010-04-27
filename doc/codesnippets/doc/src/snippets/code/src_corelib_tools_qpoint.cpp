//! [0]
p = QPoint()

p.setX(p.x() + 1)
p += QPoint(1, 0)
//! [0]


//! [1]
p = QPoint(1, 2)
#p.rx()--;   // p becomes (0, 2)
//! [1]


//! [2]
p = QPoint(1, 2)
#p.ry()++;   // p becomes (1, 3)
//! [2]


//! [3]
p = QPoint( 3, 7)
q = QPoint(-1, 4)
p += q    # p becomes (2, 11)
//! [3]


//! [4]
p = QPoint( 3, 7)
q = QPoint(-1, 4)
p -= q    # p becomes (4, 3)
//! [4]


//! [5]
p = QPoint(-1, 4)
p *= 2.5  # p becomes (-3, 10)
//! [5]


//! [6]
p = QPoint(-3, 10)
p /= 2.5  # p becomes (-1, 4)
//! [6]


//! [7]

class MyWidget(QWidget):

    self.oldPosition = QPointer()

    # event : QMouseEvent
    def mouseMoveEvent(QMouseEvent event):
        point = event.pos() - self.oldPosition
        if (point.manhattanLength() > 3):
            # the mouse has moved more than 3 pixels since the oldPosition
            pass
//! [7]


//! [8]
trueLength = sqrt(pow(x(), 2) + pow(y(), 2))
//! [8]


//! [9]
p = QPointF()

p.setX(p.x() + 1.0)
p += QPointF(1.0, 0.0)
#p.rx()++;
//! [9]


//! [10]
 p = QPointF(1.1, 2.5)
 #p.rx()--;   // p becomes (0.1, 2.5)
//! [10]


//! [11]
p = QPointF(1.1, 2.5)
#p.ry()++;   // p becomes (1.1, 3.5)
//! [11]


//! [12]
p = QPointF( 3.1, 7.1)
q = QPointF(-1.0, 4.1)
p += q    # p becomes (2.1, 11.2)
//! [12]


//! [13]
p = QPointF( 3.1, 7.1)
q = QPointF(-1.0, 4.1)
p -= q    # p becomes (4.1, 3.0)
//! [13]


//! [14]
p = QPointF(-1.1, 4.1)
p *= 2.5  # p becomes (-2.75, 10.25)
//! [14]


//! [15]
p = QPointF(-2.75, 10.25)
p /= 2.5  # p becomes (-1.1, 4.1)
//! [15]

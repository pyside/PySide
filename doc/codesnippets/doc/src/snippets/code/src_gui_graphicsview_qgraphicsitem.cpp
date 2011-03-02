//! [0]
class SimpleItem(QGraphicsItem):

    def boundingRect(self):
        penWidth = 1.0
        return QRectF(-10 - penWidth / 2, -10 - penWidth / 2,
                      20 + penWidth, 20 + penWidth)

    def paint(self, painter, option, widget):
        painter.drawRoundedRect(-10, -10, 20, 20, 5, 5)
//! [0]


//! [1]
class CustomItem(QGraphicsItem):
   ...
   self.Type = QGraphicsItem.UserType + 1

   def type(self):
       # Enable the use of qgraphicsitem_cast with this item.
       return self.Type
   ...

//! [1]


//! [2]
item.setCursor(Qt.IBeamCursor)
//! [2]


//! [3]
item.setCursor(Qt.IBeamCursor)
//! [3]


//! [4]
rect = QGraphicsRectItem()
rect.setPos(100, 100)

rect.sceneTransform().map(QPointF(0, 0))
# returns QPointF(100, 100)

rect.sceneTransform().inverted().map(QPointF(100, 100))
# returns QPointF(0, 0);
//! [4]


//! [5]
rect = QGraphicsRectItem()
rect.setPos(100, 100)

rect.deviceTransform(view.viewportTransform()).map(QPointF(0, 0))
# returns the item's (0, 0) point in view's viewport coordinates

rect.deviceTransform(view.viewportTransform()).inverted().map(QPointF(100, 100))
# returns view's viewport's (100, 100) coordinate in item coordinates
//! [5]


//! [6]
# Rotate an item 45 degrees around (0, 0)
item.rotate(45)

# Rotate an item 45 degrees around (x, y)
item.setTransform(QTransform().translate(x, y).rotate(45).translate(-x, -y))
//! [6]


//! [7]
# Scale an item by 3x2 from its origin
item.scale(3, 2)

# Scale an item by 3x2 from (x, y)
item.setTransform(QTransform().translate(x, y).scale(3, 2).translate(-x, -y))
//! [7]


//! [8]
def boundingRect(self):
    penWidth = 1.0
    return QRectF(-radius - penWidth / 2, -radius - penWidth / 2,
                  diameter + penWidth, diameter + penWidth)
//! [8]


//! [9]
def shape(self):
    path = QPainterPath()
    path.addEllipse(boundingRect())
    return path
//! [9]


//! [10]
def paint(self, painter, option, widget):
    painter.drawRoundedRect(-10, -10, 20, 20, 5, 5)
//! [10]


//! [11]
ObjectName = 0;

item = scene.itemAt(100, 50)
if len(item.data(ObjectName)) == 0:
    if isinstance(ButtonItem, item):
        item.setData(ObjectName, "Button")
//! [11]


//! [12]
scene = QGraphicsScene()
ellipse = scene.addEllipse(QRectF(-10, -10, 20, 20))
line = scene.addLine(QLineF(-10, -10, 20, 20))

line.installSceneEventFilter(ellipse)
# line's events are filtered by ellipse's sceneEventFilter() function.

ellipse.installSceneEventFilter(line)
# ellipse's events are filtered by line's sceneEventFilter() function.
//! [12]


//! [13]
def contextMenuEvent(self, event):
    menu = QMenu()
    removeAction = menu.addAction("Remove")
    markAction = menu.addAction("Mark")
    selectedAction = menu.exec(event.screenPos())
    // ...
//! [13]


//! [14]
def __init__(self):
    self.setAcceptDrops(true)
    ...

def dragEnterEvent(self, event):
    event.setAccepted(event.mimeData().hasFormat("text/plain"))
//! [14]


//! [15]
def itemChange(self, change, value):
    if change == ItemPositionChange && scene():
        # value is the new position.
        rect = scene().sceneRect()
        if !rect.contains(value):
            # Keep the item inside the scene rect.
            value.setX(qMin(rect.right(), qMax(value.x(), rect.left())))
            value.setY(qMin(rect.bottom(), qMax(value.y(), rect.top())))
            return value
    return QGraphicsItem.itemChange(self, change, value)
//! [15]


//! [16]
def setRadius(self, newRadius):
    if radius != newRadius:
        prepareGeometryChange()
        radius = newRadius
//! [16]


//! [17]
# Group all selected items together
group = scene.createItemGroup(scene.selecteditems())

# Destroy the group, and delete the group item
scene.destroyItemGroup(group)
//! [17]


//! [QGraphicsItem type]
class CustomItem(QGraphicsItem):
    ...
    self.Type = QGraphicsItem.UserType + 1

    def type(self):
       # Enable the use of qgraphicsitem_cast with this item.
       return self.Type
    ...
//! [QGraphicsItem type]

//! [18]
class QGraphicsPathItem (QAbstractGraphicsShapeItem):
    Type = 2

    def type(self):
        return QGraphicsPathItem.Type
# ...
//! [18]

//! [19]
xform = item.deviceTransform(view.viewportTransform())
deviceRect = xform.mapRect(rect).toAlignedRect()
view.viewport().scroll(dx, dy, deviceRect)
//! [19]

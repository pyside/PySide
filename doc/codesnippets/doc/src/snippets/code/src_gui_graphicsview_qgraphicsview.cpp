//! [0]
scene = QGraphicsScene()
scene.addText("Hello, world!")

view = QGraphicsView(scene)
view.show()
//! [0]


//! [1]
scene = QGraphicsScene()
scene.addRect(QRectF(-10, -10, 20, 20))

view = QGraphicsView(scene)
view.setRenderHints(QPainter.Antialiasing | QPainter.SmoothPixmapTransform)
view.show()
//! [1]


//! [2]
view = QGraphicsView()
view.setBackgroundBrush(QImage(":/images/backgroundtile.png"))
view.setCacheMode(QGraphicsView.CacheBackground)
//! [2]


//! [3]
scene = QGraphicsScene()
scene.addText("GraphicsView rotated clockwise")

view = QGraphicsView(scene)
view.rotate(90) # the text is rendered with a 90 degree clockwise rotation
view.show()
//! [3]


//! [4]
scene = QGraphicsScene()
scene.addItem(...
...

view = QGraphicsView(scene)
view.show()
...

printer = QPrinter(QPrinter.HighResolution)
printer.setPageSize(QPrinter.A4)
painter = QPainter(printer)

# print, fitting the viewport contents into a full page
view.render(painter)

# print the upper half of the viewport into the lower.
# half of the page.
viewport = view.viewport()->rect()
view.render(painter,
            QRectF(0, printer.height() / 2,
                   printer.width(), printer.height() / 2),
            viewport.adjusted(0, 0, 0, -viewport.height() / 2))

//! [4]


//! [5]
def mousePressEvent(self, event):
    print "There are", items(event->pos()).size(), "items at position", mapToScene(event->pos())
//! [5]


//! [6]
def mousePressEvent(self, event):
    if (item = itemAt(event.pos()):
        print "You clicked on item", item
    else:
        print "You didn't click on an item."
//! [6]


//! [7]
scene = QGraphicsScene()
scene.addText("GraphicsView rotated clockwise")

view = QGraphicsView(scene)
view.rotate(90) # the text is rendered with a 90 degree clockwise rotation
view.show()
//! [7]

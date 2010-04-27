//! [0]
scene = QGraphicsScene()
scene.addText("Hello, world!")

view = QGraphicsView(&scene)
view.show()
//! [0]


//! [1]
scene = QGraphicsScene
scene.addItem(...
...
printer = QPrinter(QPrinter.HighResolution)
printer.setPaperSize(QPrinter.A4)

painter = QPainter(printer)
scene.render(&painter)
//! [1]


//! [2]
segmentSize = sceneRect().size() / math.pow(2, depth - 1)
//! [2]


//! [3]
scene = QGraphicsScene()
view = QGraphicsView(scene)
view.show()

# a blue background
scene.setBackgroundBrush(Qt.blue)

# a gradient background
gradient = QRadialGradient(0, 0, 10)
gradient.setSpread(QGradient.RepeatSpread)
scene.setBackgroundBrush(gradient)
//! [3]


//! [4]
scene = QGraphicsScene()
view = QGraphicsView(scene)
view.show()

# a white semi-transparent foreground
scene.setForegroundBrush(QColor(255, 255, 255, 127))

# a grid foreground
scene.setForegroundBrush(QBrush(Qt.lightGray, Qt.CrossPattern))
//! [4]


//! [5]
class TileScene (QGraphicsScene):
    # ...
    def rectForTile(x, y):
        # Return the rectangle for the tile at position (x, y).
        return QRectF(x * self.tileWidth, y * self.tileHeight, self.tileWidth, self.tileHeight)

    def setTile(x, y, pixmap):
        # Sets or replaces the tile at position (x, y) with pixmap.
        if x >= 0 && x < self.numTilesH && y >= 0 && y < self.numTilesV:
            self.tiles[y][x] = pixmap
            invalidate(rectForTile(x, y), BackgroundLayer)

    def drawBackground(painter, exposed):
        # Draws all tiles that intersect the exposed area.
        for y in range(0, self.numTilesV:
            for x in range(0, self.numTilesH:
                rect = rectForTile(x, y)
                if exposed.intersects(rect):
                    painter.drawPixmap(rect.topLeft(), tiles[y][x])
//! [5]

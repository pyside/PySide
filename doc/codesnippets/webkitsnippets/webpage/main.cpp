//! [0]
class Thumbnailer (QObject):
    def __init__(self, url):
//! [1]
        QObject.__init__(self)
        self.page = QWebPage()
        self.page.mainFrame().load(url)
        page.loadFinished[bool].connect(self.render)
//! [1]

    finished = Signal()

//! [2]
    def render(self):
        self.page.setViewportSize(self.page.mainFrame().contentsSize())
        image = QImage(self.page.viewportSize(), QImage.Format_ARGB32)
        painter = QPainter(image)

        self.page.mainFrame().render(painter)
        painter.end()

        thumbnail = image.scaled(400, 400)
        thumbnail.save("thumbnail.png")

        self.finished.emit()
//! [2]
//! [0]

app = QApplication(sys.argv)

thumbnail = Thumbnailer(QUrl("http://qt.nokia.com"))
thumbnail.finished.connect(app.quit)
sys.exit(app.exec_())

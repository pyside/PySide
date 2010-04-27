
from PySide.QtGui import *
from PySide.QWebKit import QWebPage
from PySide.QWebKit import QWebFrame


//! [0]
class Thumbnailer(QObject):
    page = QWebPage()
//! [1]
    def __init__(self, url):
        page.mainFrame().load(url)
        connect(page, SIGNAL("loadFinished(bool)"),
                self, SLOT("render()"))
//! [1]

//! [2]
    def render(self):
        page.setViewportSize(page.mainFrame().contentsSize())
        image = QImage(page.viewportSize(), QImage.Format_ARGB32)
        painter = QPainter(image)

        page.mainFrame().render(painter)
        painter.end()

        thumbnail = image.scaled(400, 400)
        thumbnail.save("thumbnail.png")

        self.finished()
//! [2]

//! [0]

def main():
    app = QApplication([])
    thumbnail = Thumbnailer(QUrl("http://qtsoftware.com"))
    QObject.connect(thumbnail, SIGNAL("finished()"),
                    app, SLOT("quit()"))

    return app.exec_()



#include "main.moc"

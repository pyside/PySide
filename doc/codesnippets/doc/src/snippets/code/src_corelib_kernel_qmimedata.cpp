//! [0]
def dragEnterEvent(self, event):
    if event.mimeData().hasUrls():
        event.acceptProposedAction()

def dropEvent(self, event):
    if event->mimeData().hasUrls():
        for url in event.mimeData().urls():
            ...
//! [0]


//! [1]
csvData = QByteArray(...)

mimeData = QMimeData()
mimeData.setData("text/csv", csvData)
//! [1]


//! [2]
def dropEvent(self, event):
    myData = event->mimeData()
    if myData:
        # access myData's data directly (not through QMimeData's API)
}
//! [2]


//! [3]
application/x-qt-windows-mime;value="<custom type>"
//! [3]


//! [4]
application/x-qt-windows-mime;value="FileGroupDescriptor"
application/x-qt-windows-mime;value="FileContents"
//! [4]


//! [5]
if event.mimeData().hasImage():
    image = QImage(event.mimeData().imageData())
    ...
//! [5]


//! [6]
mimeData.setImageData(QImage("beautifulfjord.png"))
//! [6]


//! [7]
if event.mimeData().hasColor():
    color = QColor(event.mimeData().colorData())
    ...
//! [7]

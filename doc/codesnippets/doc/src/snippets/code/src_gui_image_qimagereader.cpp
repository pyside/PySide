//! [0]
reader = QImageReader()
reader.setFormat("png") # same as reader.setFormat("PNG")
//! [0]


//! [1]
reader = QImageReader("image.png")
# reader.format() == "png"
//! [1]


//! [2]
icon = QImage(64, 64, QImage.Format_RGB32)
reader = QImageReader("icon_64x64.bmp")
if reader.read(icon):
    # Display icon
//! [2]


//! [3]
reader = QImageReader(":/image.png")
if reader.supportsOption(QImageIOHandler.Size):
    print "Size:", str(reader.size())
//! [3]

//! [0]
writer = QImageWriter()
writer.setFormat("png") # same as writer.setFormat("PNG")
//! [0]


//! [1]
image = QImage("some/image.jpeg")
writer = QImageWriter("images/outimage.png", "png")
writer.setText("Author", "John Smith")
writer.write(image)
//! [1]


//! [2]
writer = QImageWriter(fileName)
if writer.supportsOption(QImageIOHandler.Description):
    writer.setText("Author", "John Smith")
//! [2]

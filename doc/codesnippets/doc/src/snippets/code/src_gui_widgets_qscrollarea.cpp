//! [0]
imageLabel = QLabel()
image = QImage("happyguy.png")
imageLabel.setPixmap(QPixmap.fromImage(image))

scrollArea = QScrollArea()
scrollArea.setBackgroundRole(QPalette.Dark)
scrollArea.setWidget(imageLabel)
//! [0]

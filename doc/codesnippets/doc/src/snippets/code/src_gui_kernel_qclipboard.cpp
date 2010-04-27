//! [0]
clipboard = QApplication.clipboard()
originalText = clipboard.text()
...
clipboard.setText(newText)
//! [0]


//! [1]
data = QMimeData()
data.setImageData(image)
clipboard.setMimeData(data, mode)
//! [1]

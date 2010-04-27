//! [0]
import sys

QApplication app(sys.argv)

tabWidget = QTabWidget()

scene = QGraphicsScene()
proxy = scene.addWidget(tabWidget)

view = QGraphicsView(scene)
view.show()

return app.exec_()
//! [0]

//! [1]
groupBox = QGroupBox("Contact Details")
numberLabel = QLabel("Telephone number")
numberEdit = QLineEdit()

layout = QFormLayout()
layout.addRow(numberLabel, numberEdit)
groupBox.setLayout(layout)

scene = QGraphicsScene()
proxy = scene.addWidget(groupBox)

view = QGraphicsView(scene)
view.show()
//! [1]

//! [2]
scene = QGraphicsScene()

edit = QLineEdit()
proxy = scene.addWidget(edit)

edit.isVisible()  // returns true
proxy.isVisible() // also returns true

edit.hide()

edit.isVisible()  // returns false
proxy.isVisible() // also returns false
//! [2]

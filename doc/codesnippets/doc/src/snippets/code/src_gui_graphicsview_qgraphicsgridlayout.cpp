//! [0]
scene = QGraphicsScene()
textEdit = scene.addWidget(QTextEdit())
pushButton = scene.addWidget(QPushButton())

layout = QGraphicsGridLayout()
layout.addItem(textEdit, 0, 0)
layout.addItem(pushButton, 0, 1)

form = QGraphicsWidget()
form.setLayout(layout)
scene.addItem(form)
//! [0]

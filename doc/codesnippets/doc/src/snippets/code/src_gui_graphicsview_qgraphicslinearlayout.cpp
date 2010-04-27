//! [0]
scene = QGraphicsScene()
textEdit = scene.addWidget(QTextEdit())
pushButton = scene.addWidget(QPushButton())

layout = QGraphicsLinearLayout()
layout.addItem(textEdit)
layout.addItem(pushButton)

form = QGraphicsWidget()
form.setLayout(layout)
scene.addItem(form)
//! [0]

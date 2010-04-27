//! [0]
label = QLabel(self)
label.setFrameStyle(QFrame.Panel | QFrame.Sunken)
label.setText("first line\nsecond line")
label.setAlignment(Qt.AlignBottom | Qt.AlignRight)
//! [0]


//! [1]
phoneEdit = QLineEdit(self)
phoneLabel = QLabel("&Phone:", self)
phoneLabel.setBuddy(phoneEdit)
//! [1]


//! [2]
nameEd  = QLineEdit(self)
nameLb  = QLabel("&Name:", self)
nameLb.setBuddy(nameEd)
phoneEd = QLineEdit(self)
phoneLb = QLabel("&Phone:", self)
phoneLb.setBuddy(phoneEd)
# (layout setup not shown)
//! [2]

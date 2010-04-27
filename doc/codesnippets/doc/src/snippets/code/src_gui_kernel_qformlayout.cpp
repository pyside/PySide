//! [0]
formLayout = QFormLayout()
formLayout.addRow(self.tr("&Name:"), nameLineEdit)
formLayout.addRow(self.tr("&Email:"), emailLineEdit)
formLayout.addRow(self.tr("&Age:"), ageSpinBox)
setLayout(formLayout)
//! [0]


//! [1]
nameLabel = QLabel(self.tr("&Name:"))
nameLabel.setBuddy(nameLineEdit)

emailLabel = QLabel(self.tr("&Name:"))
emailLabel.setBuddy(emailLineEdit)

ageLabel = QLabel(self.tr("&Name:"))
ageLabel.setBuddy(ageSpinBox)

gridLayout = QGridLayout()
gridLayout.addWidget(nameLabel, 0, 0)
gridLayout.addWidget(nameLineEdit, 0, 1)
gridLayout.addWidget(emailLabel, 1, 0)
gridLayout.addWidget(emailLineEdit, 1, 1)
gridLayout.addWidget(ageLabel, 2, 0)
gridLayout.addWidget(ageSpinBox, 2, 1)
setLayout(gridLayout)
//! [1]


//! [2]
formLayout.trowWrapPolicy(QFormLayout.DontWrapRows)
formLayout.setFieldGrowthPolicy(QFormLayout.FieldsStayAtSizeHint)
formLayout.setFormAlignment(Qt.AlignHCenter | Qt.AlignTop)
formLayout.setLabelAlignment(Qt.AlignLeft)
//! [2]

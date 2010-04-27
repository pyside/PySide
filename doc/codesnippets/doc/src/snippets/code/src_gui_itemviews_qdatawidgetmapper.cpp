//! [0]
mapper = QDataWidgetMapper
mapper.setModel(model)
mapper.addMapping(mySpinBox, 0)
mapper.addMapping(myLineEdit, 1)
mapper.addMapping(myCountryChooser, 2)
mapper.toFirst()
//! [0]


//! [1]
mapper = QDataWidgetMapper()
mapper.setModel(myModel)
mapper.addMapping(nameLineEdit, 0)
mapper.addMapping(ageSpinBox, 1)
//! [1]


//! [2]
mapper = QDataWidgetMapper()
connect(myTableView.selectionModel(), SIGNAL("currentRowChanged(QModelIndex,QModelIndex)"),
        mapper, SLOT(setCurrentModelIndex(QModelIndex)))
//! [2]

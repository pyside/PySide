
//! [0]
wordList = ["alpha", "omega", "omicron", "zeta"]

lineEdit = QLineEdit(self)

completer = QCompleter(wordList, self)
completer.setCaseSensitivity(Qt.CaseInsensitive)
lineEdit.setCompleter(completer)
//! [0]


//! [1]
completer = QCompleter(self)
completer.setModel(QDirModel(completer))
lineEdit.setCompleter(completer)
//! [1]


//! [2]
i = 0
while completer.setCurrentRow(i):
    print "%s is match number %d" % (completer.currentCompletion(), i)
    i += 1
//! [2]

//! [0]
model = QSqlQueryModel()
model.setQuery("select * from myTable")
if model.lastError().isValid():
    print model.lastError()
//! [0]

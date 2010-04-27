//! [0]
while myModel.canFetchMore():
    myModel.fetchMore()
//! [0]


//! [1]
model = QSqlQueryModel()
model.setQuery("select * from MyTable")
if model.lastError().isValid():
    print model.lastError()
//! [1]

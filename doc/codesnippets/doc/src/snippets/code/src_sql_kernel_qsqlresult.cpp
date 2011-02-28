//! [0]
q = QSqlQuery()
q.prepare("insert into test (i1, i2, s) values (?, ?, ?)")

col1 = [1, 3]
col2 = [2, 4]
col3 = ["hello", "world"]

q.bindValue(0, col1)
q.bindValue(1, col2)
q.bindValue(2, col3)

if not q.execBatch():
    print q.lastError()
//! [0]


//! [1]
query = QSqlQuery ...
v = query.result().handle()
if v.isValid() and (v.typeName() == "sqlite3_stmt*"):
    # v.data() returns a pointer to the handle
    handle = v.data()
    if handle != 0: # check that it is not NULL
        ...
//! [1]


//! [2]
if v.typeName() == "PGresult*":
    handle = v.data()
    if handle != 0 ...

if v.typeName() == "MYSQL_STMT*":
    handle = v.data()
    if handle != 0 ...
}
//! [2]

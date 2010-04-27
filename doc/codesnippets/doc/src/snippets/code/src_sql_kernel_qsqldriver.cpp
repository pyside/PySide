//! [0]
db = QSqlDatabase.addDatabase("SQLITE3")
v = QVariant(db.driver().handle())
if v.isValid() && v.typeName() == "sqlite3*":
    # v.data() returns a pointer to the handle
    sqlite3 *handle = *static_cast<sqlite3 **>(v.data())
    if handle != 0: # check that it is not NULL
        doSomething()
//! [0]


//! [1]
# Impossible to translate to python
if (v.typeName() == "PGconn*") {
    PGconn *handle = *static_cast<PGconn **>(v.data())
    if (handle != 0) ...
}

if (v.typeName() == "MYSQL*") {
    MYSQL *handle = *static_cast<MYSQL **>(v.data())
    if (handle != 0) ...
}
//! [1]

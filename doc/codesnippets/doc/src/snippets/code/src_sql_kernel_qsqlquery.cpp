//! [0]
SELECT forename, surname FROM people
//! [0]


//! [1]
q = QSqlQuery("select * from employees")
rec = q.record()

print "Number of columns: %d" % rec.count()

nameCol = rec.indexOf("name") # index of the field "name"
while q.next():
    print q.value(nameCol).toString() # output all names
//! [1]


//! [2]
q = QSqlQuery()
q.prepare("insert into myTable values (?, ?)")

QVariantList ints
ints << 1 << 2 << 3 << 4
q.addBindValue(ints)

QVariantList names
names << "Harald" << "Boris" << "Trond" << QVariant(QVariant.String)
q.addBindValue(names)

if not q.execBatch():
    print q.lastError()
//! [2]


//! [3]
1  Harald
2  Boris
3  Trond
4  NULL
//! [3]

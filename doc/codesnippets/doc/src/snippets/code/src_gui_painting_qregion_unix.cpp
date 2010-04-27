//! [0]
r1 = QRegion(10, 10, 20, 20)
r1.isNull()                // false
r1.isEmpty()               // false

r2 = QRegion(40, 40, 20, 20)
r3 = QRegion()
r3.isNull()                // true
r3.isEmpty()               // true

r3 = r1.intersected(r2)    // r3: intersection of r1 and r2
r3.isNull()                // false
r3.isEmpty()               // true

r3 = r1.united(r2)         // r3: union of r1 and r2
r3.isNull()                // false
r3.isEmpty()               // false
//! [0]

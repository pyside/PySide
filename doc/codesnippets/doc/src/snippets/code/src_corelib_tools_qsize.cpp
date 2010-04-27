//! [0]
t1 = QSize(10, 12)
t1.scale(60, 60, Qt.IgnoreAspectRatio)
# t1 is (60, 60)

t2 = QSize(10, 12)
t2.scale(60, 60, Qt.KeepAspectRatio)
# t2 is (50, 60)

t3 = QSize(10, 12)
t3.scale(60, 60, Qt.KeepAspectRatioByExpanding)
# t3 is (60, 72)
//! [0]


//! [1]
size = QSize(100, 10)
size.rwidth() += 20

#size becomes (120,10)
//! [1]


//! [2]
size = QSize(100, 10)
size.rheight() += 5

# size becomes (100,15)
//! [2]


//! [3]
s = QSize( 3, 7)
r = QSize(-1, 4)
s += r

# s becomes (2,11)
//! [3]


//! [4]
s = QSize( 3, 7)
r = QSize(-1, 4)
s -= r

# s becomes (4,3)
//! [4]


//! [5]
t1 = QSizeF(10, 12)
t1.scale(60, 60, Qt.IgnoreAspectRatio)
# t1 is (60, 60)

t2 = QSizeF(10, 12)
t2.scale(60, 60, Qt.KeepAspectRatio)
# t2 is (50, 60)

t3 = QSizeF(10, 12)
t3.scale(60, 60, Qt.KeepAspectRatioByExpanding)
# t3 is (60, 72)
//! [5]


//! [6]
size = QSizeF(100.3, 10)
size.rwidth() += 20.5

# size becomes (120.8,10)
//! [6]


//! [7]
size = QSizeF(100, 10.2)
size.rheight() += 5.5

# size becomes (100,15.7)
//! [7]


//! [8]
s = QSizeF( 3, 7)
r = QSizeF(-1, 4)
s += r

# s becomes (2,11)
//! [8]


//! [9]
s = QSizeF( 3, 7)
r = QSizeF(-1, 4)
s -= r

# s becomes (4,3)
//! [9]

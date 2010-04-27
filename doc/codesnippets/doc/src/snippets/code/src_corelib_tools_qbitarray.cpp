//! [0]
ba = QBitArray(200)
//! [0]


//! [1]
ba = QBitArray()
ba.resize(3)
ba[0] = True
ba[1] = False
ba[2] = True
//! [1]


//! [2]
ba = QBitArray(3)
ba.setBit(0, True)
ba.setBit(1, False)
ba.setBit(2, True)
//! [2]


//! [3]
x = QBitArray(5)
x.setBit(3, True)
# x: [ 0, 0, 0, 1, 0 ]

y = QBitArray(5)
y.setBit(4, True)
# y: [ 0, 0, 0, 0, 1 ]

x |= y
# x: [ 0, 0, 0, 1, 1 ]
//! [3]


//! [4]
QBitArray().isNull()           # returns True
QBitArray().isEmpty()          # returns True

QBitArray(0).isNull()          # returns False
QBitArray(0).isEmpty()         # returns True

QBitArray(3).isNull()          # returns False
QBitArray(3).isEmpty()         # returns False
//! [4]


//! [5]
QBitArray().isNull()           # returns True
QBitArray(0).isNull()          # returns False
QBitArray(3).isNull()          # returns False
//! [5]


//! [6]
ba = QBitArray(8)
ba.fill(True)
# ba: [ 1, 1, 1, 1, 1, 1, 1, 1 ]

ba.fill(False, 2)
# ba: [ 0, 0 ]
//! [6]


//! [7]
a = QBitArray(3)
a[0] = False
a[1] = True
a[2] = a[0] ^ a[1]
//! [7]


//! [8]
a = QBitArray(3)
b = QBitArray(2)
a[0] = 1
a[1] = 0
a[2] = 1
# a: [ 1, 0, 1 ]

b[0] = 1
b[1] = 0
# b: [ 1, 1 ]

a &= b
# a: [ 1, 0, 0 ]
//! [8]


//! [9]
a = QBitArray(3)
b = QBitArray(2)
a[0] = 1
a[1] = 0
a[2] = 1
# a: [ 1, 0, 1 ]

b[0] = 1
b[1] = 0
# b: [ 1, 1 ]

a |= b
# a: [ 1, 1, 1 ]
//! [9]


//! [10]
a = QBitArray(3)
b = QBitArray(2)
a[0] = 1
a[1] = 0
a[2] = 1
# a: [ 1, 0, 1 ]

b[0] = 1
b[1] = 0
# b: [ 1, 1 ]

a ^= b
# a: [ 0, 1, 1 ]
//! [10]


//! [11]
a = QBitArray(3)
b = QBitArray()
a[0] = 1
a[1] = 0
a[2] = 1
# a: [ 1, 0, 1 ]

b = ~a
# b: [ 0, 1, 0 ]
//! [11]


//! [12]
a = QBitArray(3)
b = QBitArray(2)
c = QBitArray()
a[0] = 1
a[1] = 0
a[2] = 1
# a: [ 1, 0, 1 ]

b[0] = 1
b[1] = 0
# b: [ 1, 1 ]

c = a & b
# c: [ 1, 0, 0 ]
//! [12]


//! [13]
a = QBitArray(3)
QBitArray b(2)
QBitArray c
a[0] = 1
a[1] = 0
a[2] = 1
# a: [ 1, 0, 1 ]

b[0] = 1
b[1] = 0
# b: [ 1, 1 ]

c = a | b
# c: [ 1, 1, 1 ]
//! [13]


//! [14]
a = QBitArray(3)
QBitArray b(2)
c = QBitArray()
a[0] = 1
a[1] = 0
a[2] = 1
# a: [ 1, 0, 1 ]

b[0] = 1
b[1] = 0
# b: [ 1, 1 ]

c = a ^ b
# c: [ 0, 1, 1 ]
//! [14]

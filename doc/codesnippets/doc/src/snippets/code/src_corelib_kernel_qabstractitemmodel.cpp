//! [0]
beginInsertRows(parent, 2, 4)
//! [0]


//! [1]
beginInsertRows(parent, 4, 5)
//! [1]


//! [2]
beginRemoveRows(parent, 2, 3)
//! [2]


//! [3]
beginInsertColumns(parent, 4, 6)
//! [3]


//! [4]
beginInsertColumns(parent, 6, 8)
//! [4]


//! [5]
beginRemoveColumns(parent, 4, 6)
//! [5]


//! [6]
beginMoveRows(sourceParent, 2, 4, destinationParent, 2)
//! [6]


//! [7]
beginMoveRows(sourceParent, 2, 4, destinationParent, 6)
//! [7]


//! [8]
beginMoveRows(parent, 2, 2, parent, 0)
//! [8]


//! [9]
beginMoveRows(parent, 2, 2, parent, 4)
//! [9]

//! [0]
model = QStandardItemModel (4, 4)
for row in range(4):
    for column in range(4):
        item = QStandardItem("row %d, column %d" % (row, column))
        model.setItem(row, column, item)
//! [0]


//! [1]
model = QStandardItemModel()
parentItem = model.invisibleRootItem()
for i in range(4):
    item = QStandardItem("item %d" % i)
    parentItem.appendRow(item)
    parentItem = item
//! [1]


//! [2]
treeView = QTreeView(self)
treeView.setModel(myStandardItemModel)
treeView.clicked[QModelIndex].connect(self.clicked)
//! [2]


//! [3]
def clicked(self, index):
    item = myStandardItemModel.itemFromIndex(index)
    # Do stuff with the item ...
//! [3]


//! [4]
treeView.scrollTo(item.index())
//! [4]

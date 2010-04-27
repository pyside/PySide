//! [0]
model = QStandardItemModel (4, 4)
for row in range(4):
    for column in range(4):
        item = QStandardItem(QString("row %0, column %1").arg(row).arg(column))
        model.setItem(row, column, item)
//! [0]


//! [1]
model = QStandardItemModel()
parentItem = model.invisibleRootItem()
for i in range(4):
    item = QStandardItem(QString("item %0").arg(i))
    parentItem.appendRow(item)
    parentItem = item
//! [1]


//! [2]
treeView = QTreeView(self)
treeView.setModel(myStandardItemModel)
connect(treeView, SIGNAL('clicked(QModelIndex)')
        this, SLOT('clicked(QModelIndex)'))
//! [2]


//! [3]
def clicked(self, index):
    item = myStandardItemModel.itemFromIndex(index)
    # Do stuff with the item ...
//! [3]


//! [4]
treeView.scrollTo(item.index())
//! [4]

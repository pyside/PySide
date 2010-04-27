//! [0]
treeWidget = QTreeWidget()
treeWidget.setColumnCount(1)
items = []
for i in range(10):
    items.append(QTreeWidgetItem(None, QStringList(QString("item: %1").arg(i))))
treeWidget.insertTopLevelItems(None, items)
//! [0]

import sys

from PySide.QtGui import QStandardItem, QStandardItemModel, QMainWindow, QTreeView, QAbstractItemView, QApplication, QMessageBox

class Item(QStandardItem):
    def __init__(self, text):
        super(Item, self).__init__()
        self.setText(text)
        self.setDragEnabled(True)
        self.setDropEnabled(True)

    def clone(self):
        ret = Item(self.text())
        return ret

class Project(QStandardItemModel):
    def __init__(self):
        super(Project, self).__init__()
        self.setItemPrototype(Item("Prototype"))
        # add some items so we have stuff to move around
        self.appendRow(Item("ABC"))
        self.appendRow(Item("DEF"))
        self.appendRow(Item("GHI"))

class MainWindow(QMainWindow):
    def __init__(self):
        super(MainWindow, self).__init__()

        self.model = Project()
        self.view = QTreeView(self)
        self.view.setModel(self.model)
        self.view.setDragEnabled(True)
        self.view.setDragDropMode(QAbstractItemView.InternalMove)
        self.setCentralWidget(self.view)

    def mousePressEvent(self, e):
        print e.x(), e.y()
        return QMainWindow.mousePressEvent(self, e)

def main():
    app = QApplication(sys.argv)
    w = MainWindow()
    w.show()
    QMessageBox.information(None, "Info", "Just drag and drop the items.")
    sys.exit(app.exec_())

if __name__ == "__main__":
    main()

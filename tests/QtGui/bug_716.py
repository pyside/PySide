from PySide.QtCore import Qt, QPersistentModelIndex
from PySide.QtGui import QStringListModel

if __name__ == '__main__':
    stringListModel = QStringListModel(['one', 'two'])
    idx = stringListModel.index(1, 0)
    persistentModelIndex = QPersistentModelIndex(idx)
    stringListModel.data(persistentModelIndex, Qt.DisplayRole)


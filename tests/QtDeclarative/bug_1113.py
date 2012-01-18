''' unit test for BUG #1113 '''

import sys
from PySide import QtCore, QtGui, QtDeclarative
import helper

class TestModel(QtCore.QAbstractListModel):
    def __init__(self, parent=None):
        super(TestModel, self).__init__(parent)
        self._data = ["one", "two", "three"]
        # this _must_ crash without the fix
        obj = QtCore.QObject()

    def rowCount(self, parent=QtCore.QModelIndex()):
        return len(self._data)

    def data(self, index, role):
        return self._data[index.row()]

if __name__ == "__main__":
    QtDeclarative.qmlRegisterType(TestModel, "Test", 1,0,
                                  "TestModel")

    app = QtGui.QApplication(sys.argv)
    view = QtDeclarative.QDeclarativeView()
    url = QtCore.QUrl.fromLocalFile(helper.adjust_filename("bug_1113.qml",
                                                           __file__))
    view.setSource(url)
    QtCore.QTimer.singleShot(70, app.quit)
    view.show()
    sys.exit(app.exec_())

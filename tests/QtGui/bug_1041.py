''' unit test for BUG #1041 '''

import sys
from PySide.QtGui import *
from PySide.QtCore import *

class BugWindow(QMainWindow):
    def __init__(self):
        super(BugWindow, self).__init__()
        self.setCentralWidget(QTableView())
        self.timer = QTimer(self)
        self.timer.timeout.connect(self.doTest)
        self.timer.start(20)
        self.count = 0

    @Slot()
    def doTest(self):
        self.m = QStandardItemModel(1, 1, None)

        try:
            table = self.centralWidget()
            table.setModel(self.m)
            table.selectionModel()
        except AttributeError:
            sys.exit(-1)

        if self.count >= 50:
            QApplication.instance().quit()

        self.count += 1

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = BugWindow()
    sys.exit(app.exec_())

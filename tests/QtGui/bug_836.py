from PySide.QtCore import *
from PySide.QtGui import *

class Mixin1(object):
    pass

class Mixin2(object):
    pass

class Mixin3(object):
    pass

class MainWindow(Mixin1, Mixin2, Mixin3, QFrame):
    def __init__(self):
        super(MainWindow, self).__init__()

def main():
    app = QApplication([])
    # if it doesn't crash it should pass
    w = MainWindow()
    w.show()
    QTimer.singleShot(0, w.close)
    app.exec_()

if __name__ == "__main__":
    main()



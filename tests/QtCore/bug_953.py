from PySide.QtCore import *

class Dispatcher(QObject):
    _me = None

    def __init__(self):
        super(Dispatcher, self).__init__()
        self._me = self
        QTimer.singleShot(0, self._finish)

    def _finish(self):
        del self._me # It can't crash here!
        QTimer.singleShot(10, QCoreApplication.instance().quit)

if __name__ == '__main__':
    app = QCoreApplication([])
    Dispatcher()
    app.exec_()

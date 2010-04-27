//! [0]
from PySide.QtCore import QApplication, QTimer

def main():

    app = QApplication([])
    QTimer.singleShot(600000, app, SLOT('quit()'))
    ...
    return app.exec()
//! [0]

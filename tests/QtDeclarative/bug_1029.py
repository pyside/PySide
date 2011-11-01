from PySide.QtCore import *
from PySide.QtGui import *
from PySide.QtDeclarative import *

import sys
import gc

def register_qml_types():
    class TestClass(QDeclarativeItem):
        def __init__(self, parent = None):
            QDeclarativeItem.__init__(self, parent)

    qmlRegisterType(TestClass, "UserTypes", 1, 0, "TestClass")

def main():
    app = QApplication([])

    # reg qml types here
    register_qml_types()

    # force gc to run
    gc.collect()

    view = QDeclarativeView()
    url = QUrl(__file__.replace(".py", ".qml"))
    view.setSource(url)

if __name__ == "__main__":
    main()

from PySide import QtCore, QtGui, QtDeclarative

import sys
import gc

def register_qml_types():
    class TestClass(QtDeclarative.QDeclarativeItem):
        def __init__(self, parent = None):
            QtDeclarative.QDeclarativeItem.__init__(self, parent)

    QtDeclarative.qmlRegisterType(TestClass, "UserTypes", 1, 0, "TestClass")

def main():
    app = QtGui.QApplication(sys.argv)

    # reg qml types here
    register_qml_types()

    # force gc to run
    gc.collect()

    view = QtDeclarative.QDeclarativeView()
    url = QtCore.QUrl(__file__.replace(".py", ".qml"))
    view.setSource(url)

if __name__ == "__main__":
    main()

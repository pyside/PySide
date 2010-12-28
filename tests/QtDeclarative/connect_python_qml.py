'''Test case for bug #442'''

from PySide import QtCore, QtGui, QtDeclarative
from helper import adjust_filename, TimedQApplication
import unittest

class TestConnectionWithInvalidSignature(TimedQApplication):
    def onButtonClicked(self):
        self.buttonClicked = True
        self.app.quit()

    def onButtonFailClicked(self):
        pass

    def testFailConnection(self):
        self.buttonClicked = False
        self.buttonFailClicked = False
        view = QtDeclarative.QDeclarativeView()
        view.setSource(QtCore.QUrl.fromLocalFile(adjust_filename('connect_python_qml.qml', __file__)))
        root = view.rootObject()
        button = root.findChild(QtCore.QObject, "buttonMouseArea")
        self.assertRaises(TypeError, QtCore.QObject.connect, [button,QtCore.SIGNAL('entered()'), self.onButtonFailClicked])
        button.entered.connect(self.onButtonClicked)
        button.entered.emit()
        view.show()
        self.app.exec_()
        self.assert_(self.buttonClicked)

if __name__ == '__main__':
    unittest.main()

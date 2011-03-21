from PySide import QtCore, QtGui, QtDeclarative
from helper import adjust_filename, TimedQApplication
import unittest

class ProxyObject(QtCore.QObject):
    def __init__(self):
        super(ProxyObject,self).__init__()
        self._o = None
        self._receivedName = ""

    @QtCore.Slot(result='QObject*')
    def getObject(self):
        if self._o:
            return self._o

        self._o = QtCore.QObject()
        self._o.setObjectName("PySideObject")
        return self._o

    @QtCore.Slot(str)
    def receivedObject(self, name):
        self._receivedName = name
 

class TestConnectionWithInvalidSignature(TimedQApplication):

    def testSlotRetur(self):
        view = QtDeclarative.QDeclarativeView()
        proxy = ProxyObject()

        context = view.rootContext()
        context.setContextProperty("proxy", proxy)
        view.setSource(QtCore.QUrl.fromLocalFile(adjust_filename('bug_726.qml', __file__)))
        root = view.rootObject()
        button = root.findChild(QtCore.QObject, "buttonMouseArea")
        view.show()
        button.entered.emit()
        self.assertEqual(proxy._receivedName, "PySideObject")

if __name__ == '__main__':
    unittest.main()

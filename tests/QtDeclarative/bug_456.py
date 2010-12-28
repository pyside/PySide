from PySide import QtCore, QtGui, QtDeclarative
from helper import adjust_filename, TimedQApplication
import unittest

class RotateValue(QtCore.QObject):
    def __init__(self):
        super(RotateValue,self).__init__()

    @QtCore.Slot(result=int)
    def val(self):
        return 100

    def setRotation(self, v):
        self._rotation = v

    def getRotation(self):
        return self._rotation

    rotation = QtCore.Property(int, getRotation, setRotation)

class TestConnectionWithInvalidSignature(TimedQApplication):

    def testSlotRetur(self):
        view = QtDeclarative.QDeclarativeView()
        rotatevalue = RotateValue()

        timer = QtCore.QTimer()
        timer.start(2000)

        context = view.rootContext()
        context.setContextProperty("rotatevalue", rotatevalue)
        view.setSource(QtCore.QUrl.fromLocalFile(adjust_filename('bug_456.qml', __file__)))
        root = view.rootObject()
        button = root.findChild(QtCore.QObject, "buttonMouseArea")
        view.show()
        button.entered.emit()
        self.assertEqual(rotatevalue.rotation, 100)

if __name__ == '__main__':
    unittest.main()

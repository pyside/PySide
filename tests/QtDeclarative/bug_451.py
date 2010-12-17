''' Test bug 451: http://bugs.openbossa.org/show_bug.cgi?id=451'''

from PySide import QtCore, QtGui, QtDeclarative
from helper import adjust_filename
import sys
import unittest

class PythonObject(QtCore.QObject):
    def __init__(self):
        QtCore.QObject.__init__(self, None)
        self._called = ""
        self._arg1 = None
        self._arg2 = None

    def setCalled(self, v):
        self._called = v

    def setArg1(self, v):
        self._arg1 = v

    def setArg2(self, v):
        self._arg2 = v

    def getCalled(self):
        return self._called

    def getArg1(self):
        return self._arg1

    def getArg2(self):
        return self._arg2

    called = QtCore.Property(str, getCalled, setCalled)
    arg1 = QtCore.Property(int, getArg1, setArg1)
    arg2 = QtCore.Property('QVariant', getArg2, setArg2)

class TestBug(unittest.TestCase):
    def testQMLFunctionCall(self):
        app = QtGui.QApplication(sys.argv)
        view = QtDeclarative.QDeclarativeView()

        obj = PythonObject()
        context = view.rootContext()
        context.setContextProperty("python", obj)
        view.setSource(QtCore.QUrl.fromLocalFile(adjust_filename('bug_451.qml', __file__)))
        root = view.rootObject()
        root.simpleFunction()
        self.assertEqual(obj.called, "simpleFunction")

        root.oneArgFunction(42)
        self.assertEqual(obj.called, "oneArgFunction")
        self.assertEqual(obj.arg1, 42)

        root.twoArgFunction(10, app)
        self.assertEqual(obj.called, "twoArgFunction")
        self.assertEqual(obj.arg1, 10)
        self.assertEqual(obj.arg2, app)

        rvalue = root.returnFunction()
        self.assertEqual(obj.called, "returnFunction")
        self.assertEqual(rvalue, 42)


if __name__ == '__main__':
    unittest.main()

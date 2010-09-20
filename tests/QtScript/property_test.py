import unittest

from PySide.QtCore import QObject, Property, QCoreApplication
from PySide.QtScript import  QScriptEngine

class MyObject(QObject):
    def __init__(self, parent = None):
        QObject.__init__(self, parent)
        self._p = 100

    def setX(self, value):
        self._p = value

    def getX(self):
        return self._p

    def resetX(self):
        self._p = 100

    def delX(self):
        self._p = 0

    x = Property(int, getX, setX, resetX, delX)


class QPropertyTest(unittest.TestCase):

    def testSimple(self):
        o = MyObject()
        self.assertEqual(o.x, 100)
        o.x = 42
        self.assertEqual(o.x, 42)

    def testHasProperty(self):
        o = MyObject()
        o.setProperty("x", 10)
        self.assertEqual(o.x, 10)
        self.assertEqual(o.property("x"), 10)

    def testMetaProperty(self):
        o = MyObject()
        m = o.metaObject()
        found = False
        for i in range(m.propertyCount()):
            mp = m.property(i)
            if mp.name() == "x":
                found = True
                break
        self.assert_(found)

    def testScriptQProperty(self):
        qapp = QCoreApplication([])
        myEngine = QScriptEngine()
        obj = MyObject()
        scriptObj = myEngine.newQObject(obj)
        myEngine.globalObject().setProperty("obj", scriptObj)
        myEngine.evaluate("obj.x = 42")
        self.assertEqual(scriptObj.property("x").toInt32(), 42)
        self.assertEqual(obj.property("x"), 42)

if __name__ == '__main__':
    unittest.main()

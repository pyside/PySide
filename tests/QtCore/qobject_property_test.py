
'''Test cases for QObject property and setProperty'''

import unittest

from PySide.QtCore import QObject, Property, Signal

class MyObjectWithNotifyProperty(QObject):
    def __init__(self, parent=None):
        QObject.__init__(self, parent)
        self.p = 0

    def readP(self):
        return self.p

    def writeP(self, v):
        self.p = v
        self.notifyP.emit()

    notifyP = Signal()
    myProperty = Property(int, readP, fset=writeP, notify=notifyP)

class PropertyWithNotify(unittest.TestCase):
    def called(self):
        self.called_ = True

    def testNotify(self):
        self.called_ = False
        obj = MyObjectWithNotifyProperty()
        obj.notifyP.connect(self.called)
        obj.myProperty = 10
        self.assert_(self.called_)

    def testHasProperty(self):
        o = MyObjectWithNotifyProperty()
        o.setProperty("myProperty", 10)
        self.assertEqual(o.myProperty, 10)
        self.assertEqual(o.property("myProperty"), 10)


if __name__ == '__main__':
    unittest.main()

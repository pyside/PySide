import unittest
from PySide import QtGui, QtCore

class Properties(unittest.TestCase):

    def testStaticProperty(self):
        self.assertEqual(QtGui.QGraphicsItem.UserType, 65536)

    def testInstanceProperty(self):
        p = QtGui.QStyleOptionViewItemV3()
        self.assert_(isinstance(p.locale, QtCore.QLocale))


if __name__ == '__main__':
    unittest.main()

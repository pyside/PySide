""" Unittest for bug #576 """
""" http://bugs.openbossa.org/show_bug.cgi?id=576 """

from PySide import QtGui, QtCore
import sys
import unittest

class Bug576(unittest.TestCase):
    def onButtonDestroyed(self, button):
        self._destroyed = True
        self.assert_(isinstance(button, QtGui.QPushButton))

    def testWidgetParent(self):
        self._destroyed = False
        app = QtGui.QApplication(sys.argv)
        w = QtGui.QWidget()

        b = QtGui.QPushButton("test")
        b.destroyed[QtCore.QObject].connect(self.onButtonDestroyed)
        self.assertEqual(sys.getrefcount(b), 2)
        b.setParent(w)
        self.assertEqual(sys.getrefcount(b), 3)
        b.parent()
        self.assertEqual(sys.getrefcount(b), 3)
        b.setParent(None)
        self.assertEqual(sys.getrefcount(b), 2)
        del b
        self.assert_(self._destroyed)


if __name__ == '__main__':
    unittest.main()


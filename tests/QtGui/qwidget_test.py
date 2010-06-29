
import unittest

from PySide.QtGui import QWidget, QMainWindow
from helper import UsesQApplication

class QWidgetInherit(QMainWindow):
    def __init__(self):
        QWidget.__init__(self)

class QWidgetTest(UsesQApplication):

    def testInheritance(self):
        self.assertRaises(TypeError, QWidgetInherit)

class QWidgetVisible(UsesQApplication):

    def testBasic(self):
        # Also related to bug #244, on existence of setVisible'''
        widget = QWidget()
        self.assert_(not widget.isVisible())
        widget.setVisible(True)
        self.assert_(widget.isVisible())


if __name__ == '__main__':
    unittest.main()

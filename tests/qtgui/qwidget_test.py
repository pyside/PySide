
import unittest

from PySide.QtGui import QWidget
from helper import UsesQApplication

class QWidgetVisible(UsesQApplication):

    def testBasic(self):
        # Also related to bug #244, on existence of setVisible'''
        widget = QWidget()
        self.assert_(not widget.isVisible())
        widget.setVisible(True)
        self.assert_(widget.isVisible())


if __name__ == '__main__':
    unittest.main()

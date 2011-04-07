import unittest
from PySide.QtGui import QToolBar, QApplication, QAction, QToolButton

class TestLabelPixmap(unittest.TestCase):
    def testReference(self):
        toolbar = QToolBar()

        for i in xrange(20):
            toolbar.addAction(QAction("Action %d" % i, None))

        buttons = toolbar.findChildren(QToolButton, "")
        toolbar.clear()

        for b in buttons:
            self.assertRaises(RuntimeError, b.objectName)

if __name__ == '__main__':
    app = QApplication([])
    unittest.main()


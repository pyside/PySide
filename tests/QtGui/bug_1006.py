import unittest
import weakref
from PySide.QtCore import Qt
from PySide.QtGui import QDialog, QLabel, QGridLayout

from helper import TimedQApplication

class LabelWindow(QDialog):
    def __init__(self, parent):
        super(LabelWindow, self).__init__(parent)

        self.test_layout = QGridLayout()
        label = QLabel("Label")
        self.test_layout.addWidget(label, 0, 0)
        self.setLayout(self.test_layout)
        self._destroyCalled = False


    def replace(self):
        old_item = self.test_layout.itemAtPosition(0, 0)
        ref = weakref.ref(old_item, self._destroyed)
        old_label = old_item.widget()
        del old_item

        self.test_layout.removeWidget(old_label)
        label = QLabel("Label New")
        old_label.deleteLater()
        label.setAlignment(Qt.AlignCenter)
        self.test_layout.addWidget(label, 0, 0)

    def _destroyed(self, obj):
        self._destroyCalled = True

class TestBug1006 (TimedQApplication):

    def testLayoutItemLifeTime(self):
        window = LabelWindow(None)
        window.replace()
        self.assertTrue(window._destroyCalled)
        self.app.exec_()

if __name__ == "__main__":
    unittest.main()

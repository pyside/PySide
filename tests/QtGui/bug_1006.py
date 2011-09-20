import unittest
import weakref
import sys

from PySide.QtCore import Qt
from PySide.QtGui import QDialog, QLabel, QGridLayout, QHBoxLayout, QWidget

from helper import TimedQApplication

class LabelWindow(QDialog):
    def __init__(self, parent):
        super(LabelWindow, self).__init__(parent)

        self.test_layout = QGridLayout()
        label = QLabel("Label")
        self.test_layout.addWidget(label, 0, 0)
        self.setLayout(self.test_layout)
        self._destroyCalled = False


    def replace(self, unit):
        old_item = self.test_layout.itemAtPosition(0, 0)
        old_label = old_item.widget()
        ref = weakref.ref(old_item, self._destroyed)

        self.test_layout.removeWidget(old_label)
        unit.assertRaises(RuntimeError, old_item.widget)
        del old_item

        label = QLabel("Label New")
        old_label.deleteLater()
        label.setAlignment(Qt.AlignCenter)
        self.test_layout.addWidget(label, 0, 0)

    def _destroyed(self, obj):
        self._destroyCalled = True

class TestBug1006 (TimedQApplication):

    def testLayoutItemLifeTime(self):
        window = LabelWindow(None)
        window.replace(self)
        self.assertTrue(window._destroyCalled)
        self.app.exec_()

    def testParentLayout(self):
        def createLayout():
            label = QLabel()
            layout = QHBoxLayout()
            layout.addWidget(label)

            widget = QWidget()
            widget.setLayout(layout)
            return (layout, widget)
        (layout, widget) = createLayout()
        item = layout.itemAt(0)
        self.assertTrue(isinstance(item.widget(), QWidget))

    def testRemoveOrphanWidget(self):
        widget = QLabel()
        layout = QHBoxLayout()
        layout.addWidget(widget)
        self.assertEqual(sys.getrefcount(widget), 3)

        layout.removeWidget(widget)
        widget.setObjectName("MyWidget")
        self.assertEqual(sys.getrefcount(widget), 2)

    def testRemoveChildWidget(self):
        parent = QLabel()
        widget = QLabel(parent)
        self.assertEqual(sys.getrefcount(widget), 3)

        layout = QHBoxLayout()
        layout.addWidget(widget)
        self.assertEqual(sys.getrefcount(widget), 3)

        layout.removeWidget(widget)
        widget.setObjectName("MyWidget")
        self.assertEqual(sys.getrefcount(widget), 3)

if __name__ == "__main__":
    unittest.main()

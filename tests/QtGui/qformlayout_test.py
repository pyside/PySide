import unittest
from PySide.QtGui import QFormLayout, QWidget

from helper import UsesQApplication

class QFormLayoutTest(UsesQApplication):

    def testGetItemPosition(self):
        formlayout = QFormLayout()
        row, role = formlayout.getItemPosition(0)
        self.assert_(isinstance(row, int))
        self.assert_(isinstance(role, QFormLayout.ItemRole))
        self.assertEqual(row, -1)

        widget = QWidget()
        formlayout.addRow(widget)
        row, role = formlayout.getItemPosition(0)
        self.assert_(isinstance(row, int))
        self.assert_(isinstance(role, QFormLayout.ItemRole))
        self.assertEqual(row, 0)
        self.assertEqual(role, QFormLayout.SpanningRole)

    def testGetWidgetPosition(self):
        formlayout = QFormLayout()
        widget = QWidget()
        row, role = formlayout.getWidgetPosition(widget)
        self.assert_(isinstance(row, int))
        self.assert_(isinstance(role, QFormLayout.ItemRole))
        self.assertEqual(row, -1)

        formlayout.addRow(widget)
        row, role = formlayout.getWidgetPosition(widget)
        self.assert_(isinstance(row, int))
        self.assert_(isinstance(role, QFormLayout.ItemRole))
        self.assertEqual(row, 0)
        self.assertEqual(role, QFormLayout.SpanningRole)

    def testGetLayoutPosition(self):
        formlayout = QFormLayout()
        layout = QFormLayout()
        row, role = formlayout.getLayoutPosition(layout)
        self.assert_(isinstance(row, int))
        self.assert_(isinstance(role, QFormLayout.ItemRole))
        self.assertEqual(row, -1)

        formlayout.addRow(layout)
        row, role = formlayout.getLayoutPosition(layout)
        self.assert_(isinstance(row, int))
        self.assert_(isinstance(role, QFormLayout.ItemRole))
        self.assertEqual(row, 0)
        self.assertEqual(role, QFormLayout.SpanningRole)


if __name__ == "__main__":
   unittest.main()


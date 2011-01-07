# trimmed down diagramscene.py to demonstrate crash in sizeHint()

import sys
from PySide import QtCore, QtGui
import unittest

class CustomWidget(QtGui.QGraphicsProxyWidget):
   def itemChange(self, eventType, value):
      QtGui.QGraphicsProxyWidget.itemChange(self, eventType, value)

class Bug589(unittest.TestCase):
   def testCase(self):
      widget = QtGui.QGraphicsProxyWidget()
      custom = CustomWidget()
      custom.setParentItem(widget)

if __name__ == "__main__":
   app = QtGui.QApplication(sys.argv)
   unittest.main()

import unittest
import sys

from helper import UsesQApplication
from PySide.QtCore import QObject, QEvent
from PySide.QtGui import QWidget

class MyFilter(QObject):
  def eventFilter(self, obj, event):
    if event.type() == QEvent.KeyPress:
      pass
    return QObject.eventFilter(self, obj, event)


class EventFilter(UsesQApplication):
    def testRefCount(self):
        o = QObject()
        filt = MyFilter()
        o.installEventFilter(filt)
        self.assertEqual(sys.getrefcount(o), 2)

        o.installEventFilter(filt)
        self.assertEqual(sys.getrefcount(o), 2)

        o.removeEventFilter(filt)
        self.assertEqual(sys.getrefcount(o), 2)

    def testObjectDestructorOrder(self):
        w = QWidget()
        filt = MyFilter()
        filt.app = self.app
        w.installEventFilter(filt)
        w.show()
        w.close()
        w = None
        self.assert_(True)

if __name__ == '__main__':
    unittest.main()

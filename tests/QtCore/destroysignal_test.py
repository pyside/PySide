from PySide.QtCore import QTimer, QObject
import sys
import unittest

class TestDestroySignal(unittest.TestCase):
    def onObjectDestroyed(self, timer):
        self.assert_(isinstance(timer, QObject))
        self._destroyed = True

    def testSignal(self):
        self._destroyed = False
        t = QTimer()
        t.destroyed[QObject].connect(self.onObjectDestroyed)
        del t
        self.assert_(self._destroyed)

    def testWithParent(self):
        self._destroyed = False
        p = QTimer()
        t = QTimer(p)
        t.destroyed[QObject].connect(self.onObjectDestroyed)
        del p
        self.assert_(self._destroyed)

if __name__ == '__main__':
    unittest.main()


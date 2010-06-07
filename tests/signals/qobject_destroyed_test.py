
import unittest

from PySide.QtCore import QObject, SIGNAL

class QObjectDestroyed(unittest.TestCase):
    """Very simple test case for the destroyed() signal of QObject"""

    def setUp(self):
        self.called = False

    def destroyed_cb(self):
        self.called = True

    def testDestroyed(self):
        """Emission of QObject.destroyed() to a python slot"""
        obj = QObject()
        QObject.connect(obj, SIGNAL('destroyed()'), self.destroyed_cb)
        del obj
        self.assert_(self.called)

if __name__ == '__main__':
    unittest.main()
